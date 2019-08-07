//QTable AREA
{
    if (++mpAgent->generalCycleCounter >= 3000)
    {
        mpAgent->generalCycleCounter = 0;

        std::cout << "Block of cycles " << ++mpAgent->countDone << ": " << mpAgent->goalCounter << " Goals" << std::endl;
        mpAgent->goalCounter = 0;
    }
    std::stringstream qTableString;
    qTableString << "qTable" << mpAgent->GetSelfUnum();
    std::ifstream qTableFileIn(qTableString.str(), std::ios::binary);
    double qTable[7][9];
    qTableFileIn.read((char *)&qTable, sizeof(qTable));
    qTableFileIn.close();

    int curState = mpAgent->lastStateOccurred;
    int actionToTake = mpAgent->lastActionTaken;
    if (curState != -1)
    {
        double reward = 0;
        int thatState = mpAgent->lastActionsState.size() ? mpAgent->lastActionsState[0] : -1;
        int thatAction = mpAgent->lastActions.size() ? mpAgent->lastActions[0] : -1;
        ServerPlayMode thatPM = mpAgent->lastActionsPM.size() ? mpAgent->lastActionsPM[0] : SPM_Null;
        vector<double> actionSpace{qTable[curState][0], qTable[curState][1], qTable[curState][2], qTable[curState][3], qTable[curState][4], qTable[curState][5], qTable[curState][6], qTable[curState][7]};
        int maxFromCurrent = greedySelection(actionSpace);
        qTable[curState][8]++;
        switch (mpObserver->GetServerPlayMode())
        {
        case SPM_Captured:
            mpAgent->cycleCounter = 0;
            mpAgent->lastActions.clear();
            mpAgent->lastActionsState.clear();
            mpAgent->lastActionsPM.clear();
            reward = 20;
            qTable[thatState][thatAction] = learn(qTable[thatState][thatAction], maxFromCurrent, reward);
            break;
        case SPM_OutOfBounds:
            mpAgent->cycleCounter = 0;
            mpAgent->lastActions.clear();
            mpAgent->lastActionsState.clear();
            mpAgent->lastActionsPM.clear();

            reward = 10;
            qTable[thatState][thatAction] = learn(qTable[thatState][thatAction], maxFromCurrent, reward);
            break;
        case SPM_Goal_Train:
            mpAgent->goalCounter++;
            mpAgent->cycleCounter = 0;
            mpAgent->lastActions.clear();
            mpAgent->lastActionsState.clear();
            mpAgent->lastActionsPM.clear();
            reward = -20;
            qTable[thatState][thatAction] = learn(qTable[thatState][thatAction], maxFromCurrent, reward);
            break;
        case SPM_TimeOut:
            mpAgent->cycleCounter = 0;
            mpAgent->lastActions.clear();
            mpAgent->lastActionsState.clear();
            mpAgent->lastActionsPM.clear();
            break;
        default:
            break;
        }
        char side = mpObserver->OurInitSide();
        Vector goal(side == 'l' ? 51.162 : -51.162, 0);
        if (mpAgent->cycleCounter == 5)
        {
            mpAgent->cycleCounter = 0;
            mpAgent->lastActions.erase(mpAgent->lastActions.begin());
            mpAgent->lastActionsState.erase(mpAgent->lastActionsState.begin());
            mpAgent->lastActionsPM.erase(mpAgent->lastActionsPM.begin());
            switch (mpObserver->GetServerPlayMode())
            {
            case SPM_PlayOn_11:
            case SPM_PlayOn_10:
            case SPM_PlayOn_9:
            case SPM_PlayOn_8:
            case SPM_PlayOn_7:
            case SPM_PlayOn_6:
            case SPM_PlayOn_5:
            case SPM_PlayOn_4:
            case SPM_PlayOn_3:
            case SPM_PlayOn_2:
            case SPM_PlayOn_1:
                if (mpAgent->lastBallPosition.Dist(goal) > mpAgent->lastGoalDist)
                {
                    if (mpAgent->lastBallPosition.Dist(mpAgent->lastPosition) < mpAgent->lastPlayerDist)
                        reward = 5;
                    else
                        reward = 2;
                }
                break;
            default:
                break;
            }

            qTable[thatState][thatAction] = learn(qTable[thatState][thatAction], maxFromCurrent, reward);
        }

        mpAgent->lastGoalDist = mpAgent->lastBallPosition.Dist(goal);
        mpAgent->lastPlayerDist = mpAgent->lastBallPosition.Dist(mpAgent->lastPosition);

        std::ofstream qTableFileOut(qTableString.str(), std::ios::binary);
        qTableFileOut.write((char *)&qTable, sizeof(qTable));
        qTableFileOut.close();
        mpAgent->cycleCounter++;
    }
}
//END OF QTable AREA