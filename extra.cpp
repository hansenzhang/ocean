
    //parallel_for(int(0), cfg.gridsize * cfg.gridsize, int(1), [](int a) {
            //cout << "Testing tbb" << endl;
    //        });
    //
    /*
    parallel_for(blocked_range<int>(1, cfg.gridsize * cfg.gridsize) , [](blocked_range<int > &r) {  
        parallel_for(int(0), cfg.gridsize * cfg.gridsize, int(i), [](int a) {
        
        });
    }); */
    /*
    for (int iter = 0; iter < cfg.iters; iter++){
        parallel_for(int(1), cfg.gridsize - 1, int(1) , [&](const int i) {  
            parallel_for(int(1), cfg.gridsize - 1, int(1), [&](const int j) {
                    top = ocean_points[locate(i - 1, j, cfg.gridsize)];
                    bottom = ocean_points[locate(i + 1, j, cfg.gridsize)];
                    left = ocean_points[locate(i, j - 1, cfg.gridsize)];
                    right = ocean_points[locate(i, j + 1, cfg.gridsize)];
                    average = (top + bottom + left + right) / 4;
                    ocean_temp[locate(i, j, cfg.gridsize)] = average;
            });
        });
        std::copy(ocean_temp, ocean_temp + (cfg.gridsize * cfg.gridsize), ocean_points); 
    }
    */ 
    
/*
    for (int iter = 0; iter < cfg.iters; iter++){
        parallel_for(int(1), cfg.gridsize - 1, int(1) , [&](const int i) {  
            parallel_for(int(1), cfg.gridsize - 1, int(1), [&](const int j) {
                    top = ocean_points[locate(i - 1, j, cfg.gridsize)];
                    bottom = ocean_points[locate(i + 1, j, cfg.gridsize)];
                    left = ocean_points[locate(i, j - 1, cfg.gridsize)];
                    right = ocean_points[locate(i, j + 1, cfg.gridsize)];
                    average = (top + bottom + left + right) / 4;
                    ocean_temp[locate(i, j, cfg.gridsize)] = average;
            });
        });
        std::copy(ocean_temp, ocean_temp + (cfg.gridsize * cfg.gridsize), ocean_points); 
    }
    */ 
    
/*
    for (int iter = 0; iter < cfg.iters; iter++){
    //affinity_partitioner ap; 

        parallel_for(blocked_range<int>(1, cfg.gridsize - 1), [&](const blocked_range<int> &r){
            for (int i = r.begin(); i != r.end(); ++i) {
                for (int j = r.begin(); j != r.end(); ++j) {
                    top = ocean_points[locate(i - 1, j, cfg.gridsize)];
                    bottom = ocean_points[locate(i + 1, j, cfg.gridsize)];
                    left = ocean_points[locate(i, j - 1, cfg.gridsize)];
                    right = ocean_points[locate(i, j + 1, cfg.gridsize)];
                    average = (top + bottom + left + right) / 4;
                    ocean_temp[locate(i, j, cfg.gridsize)] = average;
                }
            } 
        });
         
        //ocean_points = ocean_temp;
        std::copy(ocean_temp, ocean_temp + (cfg.gridsize * cfg.gridsize), ocean_points);
    } */


                ocean_temp[locate(i, j + 1, cfg.gridsize)] =
                (ocean_points[locate(i - 1, j + 1, cfg.gridsize)] + 
                ocean_points[locate(i + 1, j + 1, cfg.gridsize)] + 
                ocean_points[locate(i, j, cfg.gridsize)] + 
                ocean_points[locate(i, j + 2, cfg.gridsize)]) / 4;
                
                ocean_temp[locate(i+1, j, cfg.gridsize)] =
                (ocean_points[locate(i, j, cfg.gridsize)] + 
                ocean_points[locate(i + 2, j, cfg.gridsize)] + 
                ocean_points[locate(i+1, j - 1, cfg.gridsize)] + 
                ocean_points[locate(i+1, j + 1, cfg.gridsize)]) / 4;
                
                ocean_temp[locate(i+1, j+ 1, cfg.gridsize)] =
                (ocean_points[locate(i, j + 1, cfg.gridsize)] + 
                ocean_points[locate(i + 2, j+ 1, cfg.gridsize)] + 
                ocean_points[locate(i+1, j , cfg.gridsize)] + 
                ocean_points[locate(i+1, j + 2, cfg.gridsize)]) / 4;
