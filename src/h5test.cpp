#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mpi.h>
#include "H5Cpp.h"

using namespace H5; //<-- why not?  

int main(int argc, char* argv[]){
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  
  printf("hello from rank %d \n",rank);
  int N = atoi(argv[1]);
  printf("Rank %d will collect %d data elements from restart file\n",rank,N);
  
  const H5std_string FILE_NAME("restart.h5");
  H5File file(FILE_NAME,H5F_ACC_RDONLY);
  
  // allocate memory for incoming restart data
  float * ux;
  float * uy;
  float * uz;
  float * rho;
  
  ux = new float[N];
  uy = new float[N];
  uz = new float[N];
  rho = new float[N];
  
  const H5std_string PRESSURE("density/rho");
  const H5std_string X_VELO("velocity/x");
  const H5std_string Y_VELO("velocity/y");
  const H5std_string Z_VELO("velocity/z");
  
  DataSet p_dataset = file.openDataSet(PRESSURE);
  DataSet x_dataset = file.openDataSet(X_VELO);
  DataSet y_dataset = file.openDataSet(Y_VELO);
  DataSet z_dataset = file.openDataSet(Z_VELO);  
  
  // read data into the arrays
  p_dataset.read(rho,PredType::NATIVE_FLOAT);
  x_dataset.read(ux,PredType::NATIVE_FLOAT);
  y_dataset.read(uy,PredType::NATIVE_FLOAT);
  z_dataset.read(uz,PredType::NATIVE_FLOAT);
      
  // demonstrate that I've read the correct data
  for (int i=0; i<N; i++)
  {
    std::cout << rho[i] << " ";
  }
  std::cout << std::endl;
  
  // deallocate memory used for restart data
  delete [] ux;
  delete [] uy;
  delete [] uz;
  delete [] rho;
  
  MPI_Finalize();
  return 0;

}
