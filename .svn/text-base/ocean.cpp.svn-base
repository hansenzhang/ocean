/**
 *  Origin:  Lehigh CSE Department
 *  Course:  CSE 375/475
 *  Date:    2013-09-11
 *  Version: 1
 *
 *  Description: This file implements the ocean simulations
 *
 *  This should be the focal point for student efforts to implement their
 *  programs.
 */

#include <iostream>
#include <algorithm>

#include "tbb/tbb.h"
#include "config_t.hpp"
#include "ocean.hpp"
#define locate(x, y, z) ((x) * (z) + (y))

using namespace tbb;
using std::cout;
using std::endl;

/**
 *  An array of points, to simulate our ocean
 */
//tbb::concurrent_vector<float> ocean_points;
float* ocean_points;

/**
 *  Allocate an ocean and populate it with random floats.  Since this is an
 *  ocean simulation, we'll use reasonable celsius temperatures (e.g.,
 *  between 0 and 51), and we'll only have 3 significant digits to the right
 *  of the decimal.
 */
void init_ocean(config_t& cfg)
{
    // make a copy of the seed, since it gets modified by each call to
    // rand_r()
    unsigned seed = cfg.seed;

    //ocean_points = concurrent_vector<float>(cfg.gridsize * cfg.gridsize);
    ocean_points = new float[cfg.gridsize * cfg.gridsize];
    for (int i = 0; i < cfg.gridsize * cfg.gridsize; ++i) {
        // NB: making a random float from two random ints that we mod into a
        // reasonable range
        unsigned lhs = rand_r(&seed);
        unsigned rhs = rand_r(&seed);
        lhs = lhs % 50;
        rhs = rhs % 1000;
        float value = rhs;
        value = value / (float)1000;
        value += lhs;
        ocean_points[i] = value;
    }
}

/**
 *  When a simulation is done, we can use this to free the ocean_points data
 *  structure.
 */
void free_ocean(config_t& cfg)
{
    // We shouldn't really use free if we initialize using new
    delete []ocean_points;
}

/**
 *  Simple print routine to show the state of the ocean_points array
 */
void dump_ocean(config_t& cfg)
{
    if (!cfg.verbose)
        return;
    for (int i = 0; i < cfg.gridsize * cfg.gridsize; ++i) {
        cout << ocean_points[i];
        if ((i + 1) % cfg.gridsize == 0)
            cout << endl;
        else
            cout << ", ";
    }
}

/**
 *  Perform a sequential ocean simulation
 */
void ocean_sequential(config_t& cfg)
{
    
    float* ocean_temp = new float[cfg.gridsize * cfg.gridsize];
    std::copy(ocean_points, ocean_points + (cfg.gridsize * cfg.gridsize), ocean_temp);
    //tbb::concurrent_vector<float> ocean_temp = concurrent_vector<float> (ocean_points);
    for (int iter = 0; iter < cfg.iters; iter++){
        for (int i = 1; i < cfg.gridsize - 1; i++) {
            for (int j = 1; j < cfg.gridsize - 1; j++) {
                ocean_temp[locate(i, j, cfg.gridsize)] = 
                (ocean_points[locate(i - 1, j, cfg.gridsize)] + 
                ocean_points[locate(i + 1, j, cfg.gridsize)] + 
                ocean_points[locate(i, j - 1, cfg.gridsize)] + 
                ocean_points[locate(i, j + 1, cfg.gridsize)] + 
                ocean_points[locate(i, j, cfg.gridsize)])/ 5;
            }
        } 
        std::copy(ocean_temp, ocean_temp + (cfg.gridsize * cfg.gridsize), ocean_points);
        //ocean_points = concurrent_vector<float> (ocean_temp);
    }
    delete []ocean_temp;
}

/**
 *  Perform a parallel ocean simulation, using TBB
 */
void ocean_parallel(config_t& cfg)
{

    float* ocean_temp = new float[cfg.gridsize * cfg.gridsize];
    
    //tbb::concurrent_vector<float> ocean_temp = concurrent_vector<float> (ocean_points);
    std::copy(ocean_points, ocean_points + (cfg.gridsize * cfg.gridsize), ocean_temp);
    int grain_size;
    if (cfg.gridsize < 10)
        grain_size = 1;
    else
        grain_size = (cfg.gridsize - 2) / 4;
    affinity_partitioner ap;
    for (int iter = 0; iter != cfg.iters; ++iter){
        parallel_for(blocked_range2d<int>(1, cfg.gridsize - 1, grain_size , 1, cfg.gridsize - 1, grain_size), [=](const blocked_range2d<int> &r){
        int r_end = r.rows().end();
        int c_end = r.cols().end();
#pragma simd
        for (int i = r.rows().begin(); i != r_end; i++) {
            for (int j = r.cols().begin(); j != c_end; j++) {
                            
                ocean_temp[locate(i, j, cfg.gridsize)] = (ocean_points[locate(i - 1, j, cfg.gridsize)] +
                    ocean_points[locate(i + 1, j, cfg.gridsize)] + 
                    ocean_points[locate(i, j - 1, cfg.gridsize)] + 
                    ocean_points[locate(i, j + 1, cfg.gridsize)] +
                    ocean_points[locate(i, j, cfg.gridsize)])/ 5;
                    //int offset = locate(i, j, cfg.gridsize);
                    //__m128 m = _mm_loadu_ps((ocean_points + offset - 1));
                    //m = _mm_add_ss(m, _mm_loadu_ps((ocean_points + offset + 1)));
                    //m = _mm_add_ss(m, _mm_load_ps((ocean_points + offset - cfg.gridsize)));
                    //m = _mm_add_ss(m, _mm_load_ps((ocean_points + offset + cfg.gridsize)));
                    //m = _mm_div_ss(m, _mm_cvtepi32_ps(_mm_cvtsi32_si128(4)));
                    //_mm_storeu_ps((ocean_temp + offset), m);
                    
                }
            } 
        }, ap);
        parallel_for(blocked_range2d<int>(1, cfg.gridsize - 1, (cfg.gridsize - 2) / 4 , 1, cfg.gridsize - 1, (cfg.gridsize - 2) / 4), [=](const blocked_range2d<int> &r){
        int r_end = r.rows().end();
        int c_end = r.cols().end();
#pragma simd
        for (int i = r.rows().begin(); i != r_end; i++) {
            for (int j = r.cols().begin(); j != c_end; j++) {
                ocean_points[locate(i, j, cfg.gridsize)] = ocean_temp[locate(i, j, cfg.gridsize)]; 
                }
            } 
        }, ap);
     //ocean_points = concurrent_vector<float> (ocean_temp);
    } 
    delete []ocean_temp;
}

