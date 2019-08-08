void BehaviorDefensePlanner::Plan(std::list<ActiveBehavior> &behavior_list)
{
	std::stringstream qTableString;
	qTableString << "qTable" << mSelfState.GetUnum();
	std::ifstream qTableFileIn(qTableString.str(), std::ios::binary);
	double qTable[7][9];
	qTableFileIn.read((char *)&qTable, sizeof(qTable));
	qTableFileIn.close();
	mAgent.lastPosition = mSelfState.GetPos();
	mAgent.lastBallPosition = mWorldState.GetBall().GetPos();

	//GETTING VARIABLES
	double teammatesDistToOpp[5];
	int index = 0;
	double avgDist = 0;
	for (int i = 1; i <= 11; i++)
	{
		if (i != mWorldState.GetTeammateGoalieUnum())
		{
			double aux = mPositionInfo.GetBallDistToTeammate(i);
			teammatesDistToOpp[index++] = aux;
		}
	}
	int n = sizeof(teammatesDistToOpp) / sizeof(teammatesDistToOpp[0]);
	std::sort(teammatesDistToOpp, teammatesDistToOpp + (n));
	avgDist = teammatesDistToOpp[3] + teammatesDistToOpp[4] + teammatesDistToOpp[5] + teammatesDistToOpp[6] + teammatesDistToOpp[7] + teammatesDistToOpp[8] + teammatesDistToOpp[9];
	avgDist /= 7;
	double sum = 0;
	for (int i = 3; i < 10; i++)
	{
		sum += (teammatesDistToOpp[i] - avgDist) * (teammatesDistToOpp[i] - avgDist);
	}
	double density = sqrt(sum / 7);
	//END OF VARIABLES

	int curState;
	if (teammatesDistToOpp[0] == mPositionInfo.GetBallDistToTeammate(mSelfState.GetUnum()))
		if (teammatesDistToOpp[0] <= 5)
			curState = FirstDefenderRealClose;
		else
			curState = FirstDefender;
	else if (teammatesDistToOpp[1] == mPositionInfo.GetBallDistToTeammate(mSelfState.GetUnum()))
		curState = SecondDefender;
	else if (teammatesDistToOpp[2] == mPositionInfo.GetBallDistToTeammate(mSelfState.GetUnum()))
		curState = ThirdDefender;
	else if (density < 7)
		curState = Together;
	else if (density < 14)
		curState = MidRanged;
	else
		curState = Away;
	mAgent.lastStateOccurred = curState;
	Vector ballPosition = mWorldState.GetBall().GetPos();
	vector<double> actionSpace{qTable[curState][0], qTable[curState][1], qTable[curState][2], qTable[curState][3], qTable[curState][4], qTable[curState][5], qTable[curState][6], qTable[curState][7]};
	double epsilon = (1 - (qTable[curState][8] / 50000));
	int actionToTake = greedyEpSelection(actionSpace, epsilon > 0 ? epsilon : 0.1);
	mAgent.lastActionTaken = actionToTake;
	double power = mSelfState.CorrectDashPowerForStamina(
		ServerParam::instance().maxDashPower());
	switch (actionToTake)
	{
	case MoveNorth:
		if (mSelfState.GetPos().Y() + 2 <= 25)
			Dasher::instance().GoToPoint(mAgent, Vector(mSelfState.GetPos().X(), mSelfState.GetPos().Y() + 10), 1.0, power, false, true);
		break;
	case MoveSouth:
		if (mSelfState.GetPos().Y() - 2 >= -25)
			Dasher::instance().GoToPoint(mAgent, Vector(mSelfState.GetPos().X(), mSelfState.GetPos().Y() - 10), 1.0, power, false, true);
		break;
	case MoveWest:
		if (mSelfState.GetPos().X() - 2 >= -51)
			Dasher::instance().GoToPoint(mAgent, Vector(mSelfState.GetPos().X() - 10, mSelfState.GetPos().Y()), 1.0, power, false, true);
		break;
	case MoveEast:
		if (mSelfState.GetPos().X() + 2 >= 51)
			Dasher::instance().GoToPoint(mAgent, Vector(mSelfState.GetPos().X() + 10, mSelfState.GetPos().Y()), 1.0, power, false, true);
		break;
	case MoveToBall:
		Dasher::instance().GoToPoint(mAgent, ballPosition, 1.0, power, false, true);
		break;
	case InterceptAction:
		BehaviorInterceptPlanner(mAgent).Plan(behavior_list);
		break;
	case BlockAction:
		BehaviorBlockPlanner(mAgent).Plan(behavior_list);
		break;
	case MarkAction:
		BehaviorMarkPlanner(mAgent).Plan(behavior_list);
		break;
	case StayStill:
	default:
		break;
	}

	mAgent.lastActions.push_back(actionToTake);
	mAgent.lastActionsState.push_back(curState);
	PlayMode pm = mWorldState.GetPlayMode();
	ServerPlayMode spm = SPM_Null;
	switch (pm)
	{
	case PM_Goal_Opps:
		spm = SPM_Goal_Train;
		break;
	case PM_Captured:
		spm = SPM_Captured;
		break;
	case PM_OutOfBounds:
		spm = SPM_OutOfBounds;
		break;
	case PM_Play_On_11:
		spm = SPM_PlayOn_11;
		break;
	case PM_Play_On_10:
		spm = SPM_PlayOn_1;
		break;
	case PM_Play_On_9:
		spm = SPM_PlayOn_9;
		break;
	case PM_Play_On_8:
		spm = SPM_PlayOn_8;
		break;
	case PM_Play_On_7:
		spm = SPM_PlayOn_7;
		break;
	case PM_Play_On_6:
		spm = SPM_PlayOn_6;
		break;
	case PM_Play_On_5:
		spm = SPM_PlayOn_5;
		break;
	case PM_Play_On_4:
		spm = SPM_PlayOn_4;
		break;
	case PM_Play_On_3:
		spm = SPM_PlayOn_3;
		break;
	case PM_Play_On_2:
		spm = SPM_PlayOn_2;
		break;
	case PM_Play_On_1:
		spm = SPM_PlayOn_1;
		break;
	default:
		break;
	}
	mAgent.lastActionsPM.push_back(spm);
}