#pragma once
#ifndef MCML_IMPL_H
#define MCML_IMPL_H

using std::string;
using std::vector;

struct PhotonStruct
{
	double x, y, z; /* Cartesian coordinates.[cm] [�ѿ�������] [cm]Ϊ��λ*/
	double dcos_x, dcos_y, dcos_z;/* directional cosines of a photon. [���ӵķ�������] */
	double weight; /* weight. */
	bool dead; /* true if photon is terminated. */
	size_t layer; /* index to layer where the photon  packet resides. */
	double cur_step; /* current step size. [cm]. [��ǰ����] */
	double step_left; /* step size left. dimensionless [-]. [ʣ�ಽ��] */
};


/****
* Structure used to describe the geometry and optical [���ι�ѧ] properties of a layer.
* z0 and z1 are the z coordinates for the upper boundary  and lower boundary respectively.
* cos_crit0 and cos_crit1 are the cosines of the critical angle of total internal reflection for the
* upper boundary and lower boundary respectively.
* They are set to zero if no total internal reflection exists.
* They are used for computation speed.
****/

struct LayerStruct
{
	double z0, z1; /* z coordinates of a layer. [cm] [�������] */
	double rfct_index; /* refractive index of a layer. */
	double abs_coef; /* absorption coefficient. [1/cm] [����ϵ��]*/
	double scat_coef; /* scattering coefficient. [1/cm] [ɢ��ϵ��]*/
	double anisotropy; /* anisotropy. [�������Գ���] */
	double cos_crit_up;  /* [ȫ�ڷ����ٽ���ϱ߽������ֵ] */
	double cos_crit_down;	/*[ȫ�ڷ����ٽ���±߽������ֵ]*/
};


/****
* Input parameters for each independent run.
*
* z and r are for the cylindrical coordinate system. [cm] [Բ������ϵͳ]
* a is for the angle alpha between the photon exiting direction and the surface normal. [radian]
*
* The grid line separations in z, r, and alpha directions are dz, dr, and da respectively. The numbers
* of grid lines in z, r, and alpha directions are nz, nr, and na respectively.
*
* The member layerspecs will point to an array of structures which store parameters of each layer.
* This array has (number_layers + 2) elements. One element is for a layer.
* The layers 0 and (num_layers + 1) are for top ambient medium and the bottom ambient medium respectively.
*/

struct InputStruct
{
	string out_fname; /* output file name. */
	char out_fformat; /* output file format. */
					  /* 'A' for ASCII, */
					  /* 'B' for binary. */
	long int num_photons; /* to be traced. */
	double Wth; /* play roulette if photon */
				/* weight < Wth.*/

	double dz; /* z grid separation.[cm] */
	double dr; /* r grid separation.[cm] */
	double da; /* alpha grid separation. */
			   /* [radian] */
	size_t nz; /* array range 0..nz-1. */
	size_t nr; /* array range 0..nr-1. */
	size_t na; /* array range 0..na-1. */

	size_t num_layers; /* number of layers. */
	vector<LayerClass> layerspecs;   /* layer parameters. */
};



/*
* Classes for scoring physical quantities.
* z and r represent z and r coordinates of the [Բ������ϵ������] cylindrical coordinate system. [cm]
* a is the angle alpha between the photon exiting direction and the normal to the surfaces. [radian]
* See comments of the InputStruct.
* See manual for the physcial quantities.
*/

struct OutStruct
{
    double spec_reflect; /* specular reflectance. [-]  [���淴����]*/
    vector<vector<double>> diff_reflect_2d; /* 2D distribution of diffuse [��ά��ɢ�ֲ�] */
                                  /* reflectance. [1/(cm2 sr)] */
    vector<double> diff_reflect_rdl; /* 1D radial distribution of diffuse [һά������ɢ�ֲ�]*/
                         /* reflectance. [1/cm2] */
    vector<double> diff_reflect_agl; /* 1D angular distribution of diffuse [һά�Ƕ���ɢ�ֲ�] */
                         /* reflectance. [1/sr] */
    double diff_reflect; /* total diffuse reflectance. [-] [��������] */

    vector<vector<double>> abs_prob_rz; /* 2D probability density in turbid [��ά���Ǹ����ܶ�] */
                                 /* media over r & z. [1/cm3] */
    vector<double> abs_prob_z; /* 1D probability density over z. */
                        /* [1/cm] */
    vector<double> abs_prob_layer; /* each layer's absorption */
                        /* probability. [-] [ÿ������ո���]*/
    double abs_prob; /* total absorption probability. [-] [�����ո���] */

    vector<vector<double>> total_trans_2d; /* 2D distribution of total */
                                  /* transmittance. [1/(cm2 sr)] [��ά��͸���ʷֲ�] */
    vector<double> total_trans_rdl; /* 1D radial distribution of */
                         /* transmittance. [1/cm2] [һά����͸���ʷֲ�]*/
    vector<double> total_trans_agl; /* 1D angular distribution of */
                         /* transmittance. [1/sr] [һά��͸���ʷֲ�]*/
    double total_trans; /* total transmittance. [-] [��͸����] */
};
#endif MCML_IMPL_H
