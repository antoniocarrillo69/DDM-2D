

// Compilar usando
//   mpiCC -O1 *.cpp -o me -lm

// Iniciar ambiente de ejecucion paralelo
//   lamboot -v

// Correr usando 8 procesadores por ejemplo
//   mpirun.mpich -np 8 me

// Correr usando 4 procesadores segun lista machines.lolb por ejemplo
//   mpirun.mpich -machinefile machines.lolb -np 5 me

// Terminar ambiente de ejecucion paralelo
//   lamhalt -v




#include <stdio.h>
#include "DDM_Schur-MPI.hpp"
#include "CtrlParametros.hpp"


// Programa Maestro-Esclavo
int main(int argc, char *argv[])
{
   // Variables para MPI
   int MPI_id, MPI_np;
   MPI::Init(argc,argv);
   MPI_id = MPI::COMM_WORLD.Get_rank();
   MPI_np = MPI::COMM_WORLD.Get_size();


   // Revisa que pueda arrancar el esquema M-E
   if (MPI_np < 2)
   {
      printf("Se necesitan almenos dos procesadores para el esquema M-E\n");
      return 1;
   }

   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, argv);

   int nx = parm.intVal("nx",3);
   int ny = parm.intVal("ny",nx);
   int mx = parm.intVal("mx",nx);
   int my = parm.intVal("my",nx);
   ldouble ep = parm.doubleVal("eps",1e-5);


   DDM_Schur_MPI ddm(MPI_id,MPI_np,nx,ny,mx,my,ep);
   ddm.haz();


   MPI::Finalize();
   return 0;
}

