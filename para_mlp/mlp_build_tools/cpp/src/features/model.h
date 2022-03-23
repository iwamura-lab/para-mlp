/****************************************************************************

        Copyright (C) 2020 Atsuto Seko
                seko@cms.mtl.kyoto-u.ac.jp

        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, write to
        the Free Software Foundation, Inc., 51 Franklin Street,
        Fifth Floor, Boston, MA 02110-1301, USA, or see
        http://www.gnu.org/copyleft/gpl.txt

****************************************************************************/

#ifndef __MODEL
#define __MODEL

#include <omp.h>
#include <algorithm>

#include "mlpcpp.h"
#include "features/local.h"
#include "features/model_params.h"

//#pragma omp declare reduction( + : arma::mat : omp_out += omp_in ) \
  initializer( omp_priv = omp_orig )
//#pragma omp declare reduction( + : arma::vec : omp_out += omp_in ) \
  initializer( omp_priv = omp_orig )

class Model{

    int n_atom, n_type, model_type, maxp;
    bool force;
    ModelParams modelp;

    vector1i types;

    vector1d xe_sum;
    vector2d xf_sum, xs_sum;

    void pair
        (const vector3d& dis_array_all, const vector4d& diff_array_all,
         const vector3i& atom2_array_all, const struct feature_params& fp);

    void gtinv
        (const vector3d& dis_array, const vector4d& diff_array,
         const vector3i& atom2_array, const struct feature_params& fp);

    void model_common
        (const vector1d& de,
         const vector2d& dfx, const vector2d& dfy, const vector2d& dfz,
         const vector2d& ds, const int& type1);
    void model_linear
        (const vector1d& de,
         const vector2d& dfx, const vector2d& dfy, const vector2d& dfz,
         const vector2d& ds, int& col);
    void model1
        (const vector1d& de,
         const vector2d& dfx, const vector2d& dfy, const vector2d& dfz,
         const vector2d& ds, int& col);
    void model2_comb2
        (const vector1d& de,
         const vector2d& dfx, const vector2d& dfy, const vector2d& dfz,
         const vector2d& ds, int& col);
    void model2_comb3
        (const vector1d& de,
         const vector2d& dfx, const vector2d& dfy, const vector2d& dfz,
         const vector2d& ds, int& col);

    public:

    Model();
    Model
        (const vector3d& dis_array_all, const vector4d& diff_array_all,
         const vector3i& atom2_array_all, const vector1i& types_i,
         const struct feature_params& fp);
    ~Model();

    const vector1d& get_xe_sum() const;
    const vector2d& get_xf_sum() const;
    const vector2d& get_xs_sum() const;

};

#endif
