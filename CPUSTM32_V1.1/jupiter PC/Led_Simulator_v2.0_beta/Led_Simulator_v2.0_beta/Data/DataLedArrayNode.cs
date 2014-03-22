using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    public class LedNode
    {
        public LedNode(int newBright)
        {
            bright = newBright;
        }
        private int bright;
        public int Bright
        {
            get { return bright; }
            set
            {
                if (value < 0) bright = 0;
                else if (value > Constants.MAX_BRIGHT) bright = Constants.MAX_BRIGHT;
                else bright = value;
            }
        }
    }

    public class DataLedArrayNode
    {
        protected int ledNumber;
        protected int stateNumber;
        protected ArrayList ledData;
        public int LedNumber
        {
            get { return ledNumber; }
            set { ledNumber = value; }
        }
        public int StateNumber
        {
            get { return stateNumber; }
            set { stateNumber = value; }
        }
        public DataLedArrayNode()
        {
            ledNumber = 0;
            stateNumber = 0;
            ledData = new ArrayList();
        }
        public DataLedArrayNode(int newStateNumber, int newLedNumber)
        {
            ledNumber = newLedNumber;
            stateNumber = newStateNumber;
            ledData = new ArrayList();
            // Init default data
            for (int stateIndex = 0; stateIndex < stateNumber; stateIndex++)
            {
                // Init data for each state
                ArrayList curState = new ArrayList();
                curState.Add(Constants.StateType.Data);//Add default state type
                curState.Add(Constants.DEFAULT_BRIGHTTIME);//Add default common value for TypeStateData
                for (int ledIndex = 0; ledIndex < ledNumber; ledIndex++)
                {
                    LedNode curNode = new LedNode(Constants.DEFAULT_BRIGHT);
                    curState.Insert(ledIndex + 2, curNode);
                }
                ledData.Add(curState);
            }
        }
        public DataLedArrayNode(DataLedArrayNode newData)
        {
            LedNumber = newData.LedNumber;
            StateNumber = newData.StateNumber;
            ledData = new ArrayList();
            for (int stateIndex = 0; stateIndex < StateNumber; stateIndex++)
            {
                ArrayList curState = new ArrayList((ArrayList)newData.ledData[stateIndex]);
                ledData.Add(curState);
            }
        }
        //Implement abstract method
        //This function is used to get state of data structure and convert it to specific format
        public ArrayList GetState(int stateIndex)
        {
            ArrayList stateData = (ArrayList)ledData[stateIndex];
            ArrayList returnState = new ArrayList();
            Constants.StateType stateType = (Constants.StateType)stateData[0];
            returnState.Add(stateType);
            int stateCommonValue;
            switch (stateType)
            {
                case Constants.StateType.Data:
                    stateCommonValue = (int)stateData[1];
                    returnState.Add(stateCommonValue);
                    for (int ledIndex = 0; ledIndex < ledNumber; ledIndex++)
                    {
                        LedNode curNode = (LedNode)stateData[ledIndex + 2];
                        int ledBright = curNode.Bright;
                        returnState.Add(ledBright);
                    }
                    break;
                case Constants.StateType.StartFor:
                    stateCommonValue = (int)stateData[1];
                    returnState.Add(stateCommonValue);
                    break;
                case Constants.StateType.Endfor:
                    break;
                default:
                    return null;
            }
            return returnState;
        }

        //This function is used to get data from specific format and apply to specific index
        public Boolean SetState(int stateIndex, ArrayList stateData)
        {
            ArrayList curState = new ArrayList();
            Constants.StateType stateType = (Constants.StateType)stateData[0];
            int stateCommonValue;
            curState.Add(stateType);
            switch (stateType)
            {
                case Constants.StateType.Data:
                    stateCommonValue = (int)stateData[1];
                    curState.Add(stateCommonValue);
                    if (ledNumber < (stateData.Count-2)) ledNumber = stateData.Count-2;
                    for (int ledIndex = 0; ledIndex < ledNumber; ledIndex++)
                    {

                        int bright = (int)stateData[ledIndex + 2];
                        LedNode curNode = new LedNode(bright);
                        curState.Add(curNode);
                    }

                    break;
                case Constants.StateType.StartFor:
                    stateCommonValue = (int)stateData[1];
                    curState.Add(stateCommonValue);
                    break;
                case Constants.StateType.Endfor:
                    break;
                default:
                    return false;
            }
            ledData[stateIndex] = curState;
            return true;
        }

        public Boolean InsertState(int stateIndex, Constants.StateType stateType)
        {
            if ((stateIndex >= 0) && (stateIndex <= stateNumber))
            {
                ArrayList curState = new ArrayList();
                curState.Add(stateType);
                switch (stateType)
                {
                    case Constants.StateType.Data:
                        curState.Add(Constants.DEFAULT_BRIGHTTIME);
                        for (int ledIndex = 0; ledIndex < ledNumber; ledIndex++)
                        {
                            LedNode curNode = new LedNode(Constants.DEFAULT_BRIGHT);
                            curState.Insert(ledIndex + 2, curNode);
                        }
                        break;
                    case Constants.StateType.StartFor:
                        curState.Add(Constants.DEFAULT_LOOP_TIME);
                        break;
                    case Constants.StateType.Endfor:
                        break;
                    default:
                        return false;
                }
                ledData.Insert(stateIndex, curState);
                stateNumber++;
                return true;
            }
            return false;
        }

        public Boolean ChangeState(int stateIndex, ArrayList newState)
        {
            if (GetStateType(stateIndex) != Constants.StateType.Data)
            {
                if (newState.Count != ledNumber)
                {
                    try
                    {
                        ArrayList curState = (ArrayList)ledData[stateIndex];
                        for (int ledIndex = 0; ledIndex < LedNumber; ledIndex++)
                        {
                            LedNode curNode = (LedNode)curState[ledIndex + 2];
                            curNode.Bright = (int)newState[ledIndex];
                        }
                        return true;
                    }
                    catch (InvalidCastException e)
                    {

                        MessageBox.Show("There's exception when change state: ", e.Message);
                    }
                }
            }
            return false;
        }

        public Boolean RemoveState(int stateIndex)
        {
            if (Contains(stateIndex))
            {
                ledData.RemoveAt(stateIndex);
                stateNumber--;
                return true;
            }
            else return true;
        }
        //Override functions in DataLed class to improve performance of application
        public Constants.StateType GetStateType(int stateIndex)
        {
            if (Contains(stateIndex))
            {

                ArrayList curState = (ArrayList)ledData[stateIndex];
                if (curState != null)
                {
                    return (Constants.StateType)curState[0];
                }
            }
            return Constants.TYPE_NONE;
        }
        public int GetCommonValue(int stateIndex)
        {
            if (Contains(stateIndex))
            {

                ArrayList curState = (ArrayList)ledData[stateIndex];
                if ((curState != null) && (GetStateType(stateIndex) != Constants.StateType.Endfor))
                {
                    return (int)curState[1];
                }
            }
            return -1;
        }
        public int SetCommonValue(int stateIndex, int newValue)
        {
            if (Contains(stateIndex))
            {
                ArrayList curState = (ArrayList)ledData[stateIndex];
                if ((curState != null) && (GetStateType(stateIndex) != Constants.StateType.Endfor))
                {
                    curState[1] = newValue;
                    return (int)curState[1];
                }
            }
            return -1;
        }
        public int GetBright(int stateIndex, int ledIndex)
        {
            Constants.StateType stateType = GetStateType(stateIndex);
            if (stateType == Constants.StateType.Data)
            {
                ArrayList curState = (ArrayList)ledData[stateIndex];
                LedNode curNode = (LedNode)curState[ledIndex + 2];
                return curNode.Bright;
            }
            return -1;
        }
        public int SetBright(int stateIndex, int ledIndex, int brightValue)
        {
            Constants.StateType stateType = GetStateType(stateIndex);
            if (stateType == Constants.StateType.Data)
            {
                ArrayList curState = (ArrayList)ledData[stateIndex];
                LedNode curNode = (LedNode)curState[ledIndex + 2];
                curNode.Bright = brightValue;
                return curNode.Bright;
            }
            return -1;
        }
        public Boolean AddLed(int ledIndex)
        {
            if ((ledIndex >= 0) && (ledIndex <= ledNumber))
            {

                for (int stateIndex = 0; stateIndex < stateNumber; stateIndex++)
                {
                    ArrayList curState = (ArrayList)ledData[stateIndex];
                    Constants.StateType stateType = (Constants.StateType)curState[0];
                    switch (stateType)
                    {
                        case Constants.StateType.Data:
                            LedNode curNode = new LedNode(Constants.DEFAULT_BRIGHT);
                            curState.Insert(ledIndex + 2, curNode);
                            break;
                        case Constants.StateType.StartFor:
                        case Constants.StateType.Endfor:
                            break;
                        default:
                            return false;
                    }
                }
                ledNumber++;
                return true;
            }
            else return false;
        }


        public Boolean RemoveLed(int ledIndex)
        {
            if ((ledIndex >= 0) && (ledIndex < ledNumber))
            {
                for (int stateIndex = 0; stateIndex < stateNumber; stateIndex++)
                {
                    ArrayList curState = (ArrayList)ledData[stateIndex];
                    Constants.StateType stateType = GetStateType(stateIndex);
                    switch (stateType)
                    {
                        case Constants.StateType.Data:
                            curState.RemoveAt(ledIndex + 2);
                            break;
                        case Constants.StateType.StartFor:
                        case Constants.StateType.Endfor:
                            break;
                        default:
                            return false;
                    }
                }
                ledNumber--;
                return true;
            }
            else return false;
        }

        /* These functions is used to verify if data contain item with specify index */
        public virtual Boolean Contains(int stateIndex)
        {
            if ((stateIndex >= 0) && (stateIndex < stateNumber))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public Boolean Contains(int stateIndex, int ledIndex)
        {
            if (Contains(stateIndex))
            {
                Constants.StateType stateType = GetStateType(stateIndex);
                switch (stateType)
                {
                    case Constants.StateType.Data:
                        if ((ledIndex >= 0) && (ledIndex < ledNumber))
                        {
                            return true;
                        }
                        break;
                    case Constants.StateType.StartFor:
                    case Constants.StateType.Endfor:
                        if (ledIndex == 0) return true;
                        break;
                    default:
                        break;
                }
            }
            return false;
        }

        /* This function is used to check if for loop of data structure is valid or invalid*/
        public virtual Boolean CheckForLoop()
        {
            int startCount = 0;
            int endCount = 0;
            Constants.StateType stateType;
            for (int stateIndex = 0; stateIndex < stateNumber; stateIndex++)
            {
                stateType = GetStateType(stateIndex);
                if (stateType == Constants.StateType.None)
                {
                    return false;
                }
                if (stateType == Constants.StateType.StartFor)
                {
                    startCount++;
                }
                if (stateType == Constants.StateType.Endfor)
                {
                    endCount++;
                    if (endCount > startCount)
                    {
                        return false;
                    }
                }
            }
            if (startCount == endCount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
