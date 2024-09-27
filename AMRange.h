/**
 * @file: AMRange.h
 * Range and set of range operations
 *
 * @author Zdeněk Skulínek  &lt;<a href="mailto:me@zdenekskulinek.cz">me@zdenekskulinek.cz</a>&gt;
 */

#ifndef AMCORE_AMRANGE_H
#define AMCORE_AMRANGE_H

#include <set>
#include <algorithm>

/**
 *  @ingroup Common
 *  @{
 */

namespace AMCore {

    /**
     *  @ingroup Common
     *  @brief Range and set of range operations
     *
     *  This range means interval closed from left and open from right &lt from, to ).
     *  Template parameter may be an integer or float types.
     *  Any other class as template parameter may works, however is not tested.
     *
     *  There are basic operations for set of ranges. Set of ranges means "interval with gaps" e.q.
     *  Second interval start above first ends , thirds interval start above second end etc...
     *  Operation with set produces such set of ranges and there is a pack function to ensure this.
     */
    template<typename T>
    class AMRange
    {
    public:
        /**
         *  @brief left bound
         */
        T from;
        /**
         *  @brief right bound
         */
        T to;

        /**
         *  @brief empty constructor
         *  Uses T() for init bounds.
         *  @throw This function will not throw an exception.
         */
        AMRange();

        /**
         *  @brief empty constructor
         *  Uses T() for init bounds.
         *  @param _from bound
         *  @param _to bound
         *  @throw This function will not throw an exception.
         */
        AMRange(T _from, T _to);

        /**
         *  @brief less operator
         *  Used namely for std::set container
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline bool operator<(const AMRange &right) const;

        /**
         *  @brief minus operator
         *  Cut part of range by intersect with right operand.
         *  If ranges are in disjunction, range is unchanged.
         *  If right range is inside left (and range will be splitted to two intervals), range become invalid.
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline AMRange &operator-=(const AMRange &right);

        /**
         *  @brief plus operator
         *  Cut part of range by intersect with right operand.
         *  If right range is inside left, range is unchanged.
         *  If ranges are in disjunction (and range will splitted to two), range become invalid.
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline AMRange &operator+=(const AMRange &right);

        /**
         *  @brief comparison operator
         *  Tests both bounds for equality.
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline bool operator==(const AMRange &right) const;

        /**
         *  @brief comparison operator
         *  If at least one bound not equalt to rught bound.
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline bool operator!=(const AMRange &right) const;

        /**
         *  @brief intersect
         *  Intersection with right interval
         *  If ranges are in disjunction, range become empty
         *  @param right operand
         *  @throw This function will not throw an exception.
         */
        inline AMRange &intersect(const AMRange &right);

        /**
         *  @brief test for validity
         *  Simply checks that from bound >= to bound
         *  @throw This function will not throw an exception.
         */
        inline bool valid() const;

        /**
         *  @brief test for validity and empty
         *  Simply checks that from bound > to bound
         *  @throw This function will not throw an exception.
         */
        inline bool nonEmpty() const;

        /**
         *  @brief check that number is inside
         *  Remember that interval is open from right, so if num == to, result => false
         *  @param num
         *  @throw This function will not throw an exception.
         */
        inline bool in(T num) const;

        /**
         *  @brief check that number is inside
         *  Remember that interval is open from right, so if num == to, result => false
         *  @param rng
         *  @throw This function will not throw an exception.
         */
        inline bool in(const AMRange &rng) const;

        /**
         *  @brief test for empty
         *  Simply checks that from bound == to bound
         *  @throw This function will not throw an exception.
         */
        inline bool empty() const;
    };

    /**
     *  @brief intersect
     *  Intersection with right interval
     *  If ranges are in disjunction, returnned rage is empty
     *  @param left operand
     *  @param right operand
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    inline AMRange<T> intersect(const AMRange<T> &left, const AMRange<T> &right);
    /**
     *  @brief plus operator
     *  Cut part of range by intersect with right operand.
     *  If right range is inside left, returned range is left range.
     *  If ranges are in disjunction (and range will splitted to two), returned range is invalid.
     *  @param left operand
     *  @param right operand
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    inline AMRange<T> operator+(const AMRange<T> &left, const AMRange<T> &right);
    /**
     *  @brief minus operator
     *  Cut part of range by intersect with right operand.
     *  If ranges are in disjunction, range is unchanged.
     *  If right range is inside left (and range will be splitted to two intervals), range become invalid.
     *  @param left operand
     *  @param right operand
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    inline AMRange<T> operator-(const AMRange<T> &left, const AMRange<T> &right);

    /**
     *  @brief packed test
     *  Set of ranges is packed when, ranges has not intersections. E.q. Second range starts above first range end,
     *  third range start above second range end.
     *  Packed set of ranges also when, ranges are not splitted, E.q. range right bound not equal another range left bound
     *  @param s set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    bool isPacked(const std::set<AMRange<T> > &s);
    /**
     *  @brief valid test
     *  Set of ranges is valid when all range in are valid
     *  @param s set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    bool valid(const std::set<AMRange<T> > &s);
    /**
     *  @brief pack a set of ranges
     *  Set of ranges is packed when, ranges has not intersections. E.q. Second range starts above first range end,
     *  third range start above second range end.
     *  Packed set of ranges also when, ranges are not splitted, E.q. range right bound not equal another range left bound
     *  @param s set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > pack(const std::set<AMRange<T> > &s);
    template<typename T>
    /**
     *  @brief plus operator
     *  Adds two set of ranges.
     *  Sets of range must be valid.
     *  Result set of ranges is packed.
     *  @param left set of ranges
     *  @param right set of ranges
     *  @throw This function will not throw an exception.
     */
    std::set<AMRange<T> > operator+(const std::set<AMRange<T> > &left, const std::set<AMRange<T> > &right);
    /**
     *  @brief minus operator
     *  Subtracts two set of ranges.
     *  Sets of ranges must be valid.
     *  Result set of ranges is packed.
     *  @param left set of ranges
     *  @param right set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > operator-(const std::set<AMRange<T> > &left, const std::set<AMRange<T> > &right);
    /**
     *  @brief plus operator
     *  Adds range and  set of ranges.
     *  Set of range mus be valid.
     *  Result set of ranges is packed.
     *  @param left range
     *  @param right set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > operator+(const AMRange<T> &left, const std::set<AMRange<T> > &right);
    /**
     *  @brief minus operator
     *  Subtracts range and  set of ranges.
     *  Set of range mus be valid.
     *  Result set of ranges is packed.
     *  @param left range
     *  @param right set of ranges
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > operator-(const AMRange<T> &left, const std::set<AMRange<T> > &right);
    /**
     *  @brief plus operator
     *  Adds set of ranges and range
     *  Set of range must be valid.
     *  Result set of ranges is packed.
     *  @param left set of ranges
     *  @param right range
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > operator+(const std::set<AMRange<T> > &left, const AMRange<T> &right);
    /**
     *  @brief minus operator
     *  Subtracts set of ranges and range
     *  Set of range must be valid.
     *  Result set of ranges is packed.
     *  @param left set of ranges
     *  @param right range
     *  @throw This function will not throw an exception.
     */
    template<typename T>
    std::set<AMRange<T> > operator-(const std::set<AMRange<T> > &left, const AMRange<T> &right);


    template<typename T>
    AMRange<T>::AMRange()
        : from(),
          to()
    {
    };

    template<typename T>
    AMRange<T>::AMRange(T _from, T _to)
        : from(_from),
          to(_to)
    {
    };

    template<typename T>
    inline bool AMRange<T>::operator<(const AMRange<T> &right) const
    {
        if (from < right.from)  {
            return true;
        } else if (from == right.from) {
            return to < right.to;
        }
        return false;
    }

    template<typename T>
    inline AMRange<T> &AMRange<T>::operator-=(const AMRange<T> &right)
    {
        if (!valid()) {
            return *this;
        }
        if (!right.valid()) {
            from = right.from;
            to = right.to;
            return *this;
        }
        if (from < right.from) {
            if (to > right.to) {
                T t = to;
                to = from;
                from = t;
            }else if (to > right.from) {
                to = right.from;
            }
        } else {
            if (to < right.to) {
                to = from;
            } else if (from < right.to) {
                from = right.to;
            }
        }
        return *this;
    }

    template<typename T>
    inline AMRange<T> &AMRange<T>::intersect(const AMRange<T> &right)
    {
        if (from < right.from) {
            from = right.from;
        }
        if (to > right.to) {
            to = right.to;
        }
        if (to < from) {
            to = from;
        }
        return *this;
    }

    template<typename T>
    inline AMRange<T> &AMRange<T>::operator+=(const AMRange<T> &right)
    {
        if (!valid()) {
            return *this;
        }
        if (!right.valid()) {
            from = right.from;
            to = right.to;
            return *this;
        }
        if (to < right.from || from > right.to) {
            if (from == to) {
                from = right.from;
                to = right.to;
            } else {
                T t = to;
                to = from;
                from = t;
            }
        } else {
            if (to < right.to) {
                to = right.to;
            }
            if (from > right.from) {
                from = right.from;
            }
        }
        return *this;
    }

    template<typename T>
    inline bool AMRange<T>::operator==(const AMRange<T> &right) const
    {
        return (from == right.from && to == right.to);
    }

    template<typename T>
    inline bool AMRange<T>::operator!=(const AMRange<T> &right) const
    {
        return (from != right.from || to != right.to);
    }


    template<typename T>
    inline bool AMRange<T>::valid() const
    {
        return (to >= from);
    }

    template<typename T>
    inline bool AMRange<T>::in(T num) const
    {
        return ((num >= from) && (num < to));
    }

    template<typename T>
    inline bool AMRange<T>::empty() const
    {
        return to == from;
    }

    template<typename T>
    inline bool AMRange<T>::nonEmpty() const
    {
        return to > from;
    }

    template<typename T>
    inline bool AMRange<T>::in(const AMRange<T> &_rng) const
    {
        return ((_rng.from >= from) && (_rng.to <= to) && (_rng.from < _rng.to));
    }

    template<typename T>
    inline AMRange<T> operator+(const AMRange<T> &left, const AMRange<T> &right)
    {
        AMRange<T> r = left;
        r += right;
        return r;
    }

    template<typename T>
    inline AMRange<T> operator-(const AMRange<T> &left, const AMRange<T> &right)
    {
        AMRange<T> r = left;
        r -= right;
        return r;
    }

    template<typename T>
    inline AMRange<T> intersect(const AMRange<T> &left, const AMRange<T> &right)
    {
        AMRange<T> r = left;
        r.intersect(right);
        return r;
    }

    template<typename T>
    bool isPacked(const std::set<AMRange<T> > &s)
    {
        typename std::set<AMRange<T> >::iterator it = s.begin();
        if (it == s.end()) {
            return true;
        }
        typename std::set<AMRange<T> >::iterator itn = it;
        if (!itn->valid()) {
            return false;
        }
        itn++;
        while (itn != s.end()) {
            if (itn->from > it->to) {
                if (!itn->valid()) {
                    return false;
                }
                it = itn;
                itn++;
                continue;
            }
            return false;
        }
        return true;
    }

    template<typename T>
    bool valid(const std::set<AMRange<T> > &s)
    {
        for(typename std::set<AMRange<T> >::iterator it = s.begin(); it != s.end(); it++) {
            if (!it->valid()) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    std::set<AMRange<T> > pack(const std::set<AMRange<T> > &s)
    {
        AMRange<T> r;
        std::set<AMRange<T> > result;
        bool start = true;
        typename std::set<AMRange<T> >::iterator it = s.begin();

        do {
            do {
                if (it == s.end()) {
                    if (!start) {
                        result.insert(r);
                    }
                    return result;
                }
                if (it->valid()) {
                    break;
                }
                it++;
            } while (1);

            if (start) {
                r = *it;
                start = false;
                continue;
            }
            AMRange<T> rx = r + *it;
            if (rx.valid()) {
                r = rx;
            } else {
                result.insert(r);
                r = *it;
            }
            it++;
        } while(1);
    }

    template<typename T>
    std::set<AMRange<T> > operator+(const std::set<AMRange<T> > &left, const std::set<AMRange<T> > &right)
    {
        std::set<AMRange<T> > result = left;
        std::merge(left.begin(), left.end(),
            right.begin(), right.end(),
            std::inserter(result, result.begin()));
        result = pack(result);
        return result;
    }

    template<typename T>
    std::set<AMRange<T> > operator-(const std::set<AMRange<T> > &left, const std::set<AMRange<T> > &right)
    {
        if (left.size() == 0) {
            return std::set<AMRange<T> >();
        }
        if (right.size() == 0) {
            return left;
        }
        std::set<AMRange<T> > ls = pack(left);
        std::set<AMRange<T> > rs = pack(right);
        std::set<AMRange<T> > result;
        typename std::set<AMRange<T> >::iterator lit = ls.begin();
        typename std::set<AMRange<T> >::iterator rit = rs.begin();
        AMRange<int> r = *lit;
        while (1) {
            if (lit != ls.end()) {
                if (rit != rs.end()) {
                    AMRange<T> tr = r - *rit;
                    if (!tr.valid()) {
                        AMRange ir(r.from, rit->from);
                        if (ir.nonEmpty()) {
                            result.insert(ir);
                        }
                        r.from = rit->to;
                    } else {
                        r = tr;
                    }
                    if (lit->to > rit->to) {
                        rit++;
                    } else {
                        lit++;
                        if (lit != ls.end()) {
                            if (r.nonEmpty()) {
                                result.insert(r);
                            }
                            r = *lit;
                        }
                    }
                } else {
                    lit++;
                    if (lit != ls.end()) {
                        if (r.nonEmpty()) {
                            result.insert(r);
                        }
                        r = *lit;
                    }
                }
            } else {
                if (rit != rs.end()) {
                    rit++;
                } else {
                    break;
                }
            }
        }
        if (r.nonEmpty()) {
            result.insert(r);
        }
        return result;
    }

    template<typename T>
    std::set<AMRange<T> > operator+(const AMRange<T> &left, const std::set<AMRange<T> > &right)
    {
        std::set<AMRange<T> > result = right;
        result.insert(left);
        result = pack(result);
        return result;
    }
    template<typename T>
    std::set<AMRange<T> > operator-(const AMRange<T> &left, const std::set<AMRange<T> > &right)
    {
        std::set<AMRange<T> > ls = {left};
        return ls - right;
    }
    template<typename T>
    std::set<AMRange<T> > operator+(const std::set<AMRange<T> > &left, const AMRange<T> &right)
    {
        std::set<AMRange<T> > result = left;
        result.insert(right);
        result = pack(result);
        return result;
    }
    template<typename T>
    std::set<AMRange<T> > operator-(const std::set<AMRange<T> > &left, const AMRange<T> &right)
    {
        std::set<AMRange<T> > rs = {right};
        return left - rs;
    }
}

/** @} */

#endif //AMCORE_AMRANGE_H
