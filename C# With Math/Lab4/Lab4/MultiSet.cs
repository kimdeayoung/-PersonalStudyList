using System.Collections.Generic;
using System.Text;

namespace Lab4
{
    public sealed class MultiSet
    {
        List<string> SetDatas = new List<string>();

        public int Count()
        {
            return SetDatas.Count;
        }

        public string GetSortString()
        {
            string sortString = string.Empty;

            StringBuilder stringBuilder = new StringBuilder();
            for (int i = 0; i < SetDatas.Count; ++i)
            {
                stringBuilder.Append(SetDatas[i]);
                if (i < SetDatas.Count - 1)
                {
                    stringBuilder.Append(",");
                }
            }

            return stringBuilder.ToString();
        }

        public void Add(string element)
        {
            SetDatas.Add(element);
        }

        public bool Remove(string element)
        {
            return SetDatas.Remove(element);
        }

        public uint GetMultiplicity(string element)
        {
            uint multiplicityCount = 0;
            for (int i = 0; i < SetDatas.Count; ++i)
            {
                if (SetDatas[i] == element)
                {
                    ++multiplicityCount;
                }
            }
            return multiplicityCount;
        }

        public List<string> ToList()
        {
            List<string> result = new List<string>();
            for (int i = 0; i < SetDatas.Count; ++i)
            {
                result.Add(SetDatas[i]);
            }
            result.Sort();

            return result;
        }

        public MultiSet Union(MultiSet other)
        {
            MultiSet result = new MultiSet();
            List<string> otherMultiSetDatas = other.ToList();

            for (int i = 0; i < SetDatas.Count; ++i)
            {
                string setData = SetDatas[i];
                result.Add(setData);
                otherMultiSetDatas.Remove(setData);
            }

            for (int i = 0; i < otherMultiSetDatas.Count; ++i)
            {
                string setData = otherMultiSetDatas[i];
                result.Add(setData);
            }

            return result;
        }

        public MultiSet Intersect(MultiSet other)
        {
            List<string> copyedSetDatas = this.ToList();
            List<string> otherMultiSetDatas = other.ToList();

            List<string> loopingList = copyedSetDatas;
            List<string> findTargetList = otherMultiSetDatas;

            if (copyedSetDatas.Count < otherMultiSetDatas.Count)
            {
                loopingList = otherMultiSetDatas;
                findTargetList = copyedSetDatas;
            }

            MultiSet result = new MultiSet();
            for (int i = 0; i < loopingList.Count; ++i)
            {
                string findValue = loopingList[i];
                bool bIsFind = findTargetList.Remove(findValue);
                if (bIsFind == true)
                {
                    result.Add(findValue);
                    if (findTargetList.Count <= 0)
                    {
                        break;
                    }
                }
            }

            return result;
        }

        public MultiSet Subtract(MultiSet other)
        {
            List<string> otherMultiSetDatas = other.ToList();

            List<string> loopingList = SetDatas;

            MultiSet result = new MultiSet();
            for (int i = 0; i < loopingList.Count; ++i)
            {
                string findValue = loopingList[i];
                bool bIsFind = otherMultiSetDatas.Remove(findValue);
                if (bIsFind == false)
                {
                    result.Add(findValue);
                }
            }

            return result;
        }

        public List<MultiSet> FindPowerSet()
        {
            List<string> dataList = this.ToList();

            List<MultiSet> findPowersetResults = new List<MultiSet>();

            int[] insertAbleFlags = new int[dataList.Count];
            for (int i = 0; i < insertAbleFlags.Length; ++i)
            {
                insertAbleFlags[i] = 0;
            }
            GetPowersetRecursive(ref findPowersetResults, dataList, insertAbleFlags, 0);

            List<string> resultSortingList = new List<string>();
            for (int i = 0; i < findPowersetResults.Count;)
            {
                string sortString = findPowersetResults[i].GetSortString();

                if (resultSortingList.Contains(sortString) == true)
                {
                    findPowersetResults.RemoveAt(i);
                }
                else
                {
                    resultSortingList.Add(sortString);
                    ++i;
                }
            }
            resultSortingList.Sort();

            List<MultiSet> result = new List<MultiSet>();
            for (int i = 0; i < resultSortingList.Count; ++i)
            {
                string resultSortString = resultSortingList[i];

                for (int j = 0; j < findPowersetResults.Count; ++j)
                {
                    string powerSetResultSortString = findPowersetResults[j].GetSortString();
                    if (resultSortString.Contains(powerSetResultSortString) == true)
                    {
                        result.Add(findPowersetResults[j]);
                        findPowersetResults.RemoveAt(j);
                        break;
                    }
                }
            }

            return result;
        }

        void GetPowersetRecursive(ref List<MultiSet> resultMultiSets, List<string> strDatas, int[] insertAbleFlag, int depth)
        {
            if (depth >= strDatas.Count)
            {
                MultiSet newMultiSet = new MultiSet();
                for (int i = 0; i < insertAbleFlag.Length; ++i)
                {
                    if (insertAbleFlag[i] == 1)
                    {
                        newMultiSet.Add(strDatas[i]);
                    }
                }
                resultMultiSets.Add(newMultiSet);
                return;
            }

            insertAbleFlag[depth] = 1;
            GetPowersetRecursive(ref resultMultiSets, strDatas, insertAbleFlag, depth + 1);

            insertAbleFlag[depth] = 0;
            GetPowersetRecursive(ref resultMultiSets, strDatas, insertAbleFlag, depth + 1);
        }

        public bool IsSubsetOf(MultiSet other)
        {
            MultiSet intersectResult = Intersect(other);
            if (SetDatas.Count == intersectResult.Count())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool IsSupersetOf(MultiSet other)
        {
            if (other.Count() == 0)
            {
                return true;
            }

            MultiSet intersectResult = Intersect(other);
            if (other.Count() == intersectResult.Count())
            {
                if (SetDatas.Count >= other.Count())
                {
                    return true;
                }
            }
            return false;
        }
    }
}
