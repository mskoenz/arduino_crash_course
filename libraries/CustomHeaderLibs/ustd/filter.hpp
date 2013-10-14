// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    23.07.2013 05:09:46 EDT
// File:    filter.hpp

#ifndef __FILTER_HEADER
#define __FILTER_HEADER

#include "filter/identity.hpp"
#include "filter/lowpass.hpp"
#include "filter/highpass.hpp"
#include "filter/hysteresis.hpp"

namespace ustd {
    template< typename T
            , typename tag0 = tag::identity
            , typename tag1 = tag::identity
            , typename tag2 = tag::identity
            , typename tag3 = tag::identity
            , typename tag4 = tag::identity
            , typename tag5 = tag::identity
            , typename tag6 = tag::identity
            , typename tag7 = tag::identity
            , typename tag8 = tag::identity
            , typename tag9 = tag::identity
            , typename end_tag = tag::identity //leave this default! else something is derived form void
            >
    using filter = typename realization<T, tag0
                    , typename realization<T, tag1
                        , typename realization<T, tag2
                            , typename realization<T, tag3
                                , typename realization<T, tag4
                                    , typename realization<T, tag5
                                        , typename realization<T, tag6
                                            , typename realization<T, tag7
                                                , typename realization<T, tag8
                                                    , typename realization<T, tag9
                                                        , typename realization<T, end_tag, void>::type 
                                                        >::type 
                                                    >::type 
                                                >::type 
                                            >::type 
                                        >::type 
                                    >::type 
                                >::type 
                            >::type 
                        >::type 
                    >::type;
}//end namespace ustd
#endif //__FILTER_HEADER
