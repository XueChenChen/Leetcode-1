class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int m = ((l+r) >> 1);
            int mVal = nums[m];
            
            //printf("Checking l == %d, r == %d, m == %d\n\tmVal == %d, target == %d\n", l, r, m, mVal, target);
            
            if (nums[l] < mVal && mVal < nums[r-1]) {
                //printf("\tin a monotonic sequence\n");
                if (nums[l] <= target && target <= nums[r-1]) {
                    //printf("\ttarget is within this monotonic sequence\n");
                    if (mVal == target) {
                        return m;
                    } else if (mVal < target) {
                        l = m+1;
                    } else {
                        r = m;
                    }
                } else {
                    // Not findable.
                    return -1;
                }
            } else {
                // There is a kink in [l, r).
                //printf("\tthere's a kink within [%d, %d)\n", l, r);
                if (mVal == target) {
                    return m;
                } else if (mVal > target) {
                    if (mVal >= nums[l]) {
                        if (target >= nums[l]) {
                            //printf("\tmVal:%d > target:%d >= nums[l]:%d\n", mVal, target, nums[l]);
                            // both m & target are on the left half of the kink
                            r = m;
                        } else {
                            // target < nums[l]
                            if (target <= nums[r-1]) {
                                //printf("\tmVal:%d > nums[r-1]:%d >= target:%d\n", mVal, nums[r-1], target);
                                l = m+1;
                            } else {
                                // Not findable.
                                return -1;
                            }
                        }    
                    } else {
                        // mVal < nums[l], it's implicit that "mVal <= nums[r-1]" and thus "target < mVal <= nums[r-1]" in this case
                        r = m;
                    }
                } else {
                    // mVal < target
                    if (mVal >= nums[l]) {
                        //printf("\ttarget:%d > mVal:%d >= nums[l]:%d\n", target, mVal, nums[l]);
                        // it's implicit that "nums[l] <= mVal < target"
                        l = m+1;
                    } else {
                        // mVal < nums[l], it's implicit that "mVal <= nums[r-1]" and thus "target < mVal <= nums[r-1]" in this case
                        if (target >= nums[l]) {
                            //printf("\ttarget:%d >= nums[l]:%d > mVal:%d\n", target, nums[l], mVal);
                            r = m;
                        } else {
                            // target < nums[l]
                            if (target <= nums[r-1]) {
                                //printf("\tnums[r-1]:%d >= target:%d > mVal:%d\n", nums[r-1], target, mVal);
                                l = m+1;
                            } else {
                                // Not findable.
                                return -1;
                            }   
                        }
                    }
                }
            }
        }
        return -1;
    }
};
