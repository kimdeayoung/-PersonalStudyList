using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6
{
    public class Recyclebot
    {
        private List<Item> mRecycleItems;
        private List<Item> mNonRecycleItems;

        public Recyclebot()
        {
            mRecycleItems = new List<Item>();
            mNonRecycleItems = new List<Item>();
        }

        public List<Item> RecycleItems { get => mRecycleItems; }
        public List<Item> NonRecycleItems { get => mNonRecycleItems; }

        public void Add(Item item)
        {
            const double MIN_WEIGHT = 2.0;
            const double MAX_WEIGHT = 5.0;

            switch (item.Type)
            {
                case EType.Paper:
                case EType.Furniture:
                case EType.Electronics:
                    if (item.Weight >= MIN_WEIGHT && item.Weight < MAX_WEIGHT)
                    {
                        mRecycleItems.Add(item);
                    }
                    else
                    {
                        mNonRecycleItems.Add(item);
                    }
                    break;
                default:
                    mRecycleItems.Add(item);
                    break;
            }
        }

        public List<Item> Dump()
        {
            List<Item> resultItems = new List<Item>();

            for (int i = 0; i < mNonRecycleItems.Count; ++i)
            {
                Item nonRecycleItem = mNonRecycleItems[i];

                if (IsFirstPremiseValue(nonRecycleItem.Volume) == true)
                {//10,11,15가 아닐때
                    if (nonRecycleItem.IsToxicWaste == true)
                    {
                        switch (nonRecycleItem.Type)
                        {
                            case EType.Electronics:
                            case EType.Furniture:
                                resultItems.Add(nonRecycleItem);
                                break;
                        }
                    }
                    else
                    {
                        resultItems.Add(nonRecycleItem);
                    }
                }
                else
                {//10,11,15일때
                    switch (nonRecycleItem.Type)
                    {
                        case EType.Electronics:
                        case EType.Furniture:
                            resultItems.Add(nonRecycleItem);
                            break;
                    }
                }
            }

            return resultItems;
        }

        bool IsSameValue(double value1, double value2)
        {
            if (Math.Abs(value1 - value2) <= double.Epsilon)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool IsFirstPremiseValue(double compareVolume)
        {
            bool bResult = true;
            if (IsSameValue(compareVolume, 10.0) == true)
            {
                bResult = false;
            }
            else if (IsSameValue(compareVolume, 11.0) == true)
            {
                bResult = false;
            }
            else if (IsSameValue(compareVolume, 15.0) == true)
            {
                bResult = false;
            }

            return bResult;
        }
    }
}
