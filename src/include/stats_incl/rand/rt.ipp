/*################################################################################
  ##
  ##   Copyright (C) 2011-2022 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * Sample from the t-distribution
 */

//
// scalar output

namespace internal
{

template<typename T>
statslib_inline
T
rt_compute(const T dof_par, rand_engine_t& engine)
{
    if (!t_sanity_check(dof_par)) {
        return STLIM<T>::quiet_NaN();
    }

    //

    T numer = rnorm(T(0),T(1),engine);
    
    return numer / std::sqrt( rchisq(dof_par,engine) / dof_par );
}

}

template<typename T>
statslib_inline
return_t<T>
rt(const T dof_par, rand_engine_t& engine)
{
    return internal::rt_compute(static_cast<return_t<T>>(dof_par),engine);
}

template<typename T>
statslib_inline
return_t<T>
rt(const T dof_par, const ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rt(dof_par,engine);
}

//
// matrix output

namespace internal
{

#ifdef STATS_ENABLE_INTERNAL_VEC_FEATURES
template<typename T1, typename rT>
statslib_inline
void
rt_vec(const T1 dof_par, rT* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rt,vals_out,num_elem,dof_par);
}
#endif

#ifdef STATS_ENABLE_STDVEC_WRAPPERS
template<typename eT, typename T1>
statslib_inline
void
rt_mat_check(std::vector<eT>& X, const T1 dof_par)
{
    STDVEC_RAND_DIST_FN(rt,dof_par);
}
#endif

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename T1>
statslib_inline
void
rt_mat_check(mT& X, const T1 dof_par)
{
    MAIN_MAT_RAND_DIST_FN(rt,dof_par);
}
#endif

}

#ifdef STATS_ENABLE_INTERNAL_VEC_FEATURES
template<typename mT, typename T1>
statslib_inline
mT
rt(const ullint_t n, const ullint_t k, const T1 dof_par)
{
    GEN_MAT_RAND_FN(rt_mat_check,dof_par);
}
#endif