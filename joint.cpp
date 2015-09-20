#include<fstream>
#include<iostream>
#include<string>
#include <cstdlib>

using namespace std;

int MAX_ATOM=40000;

int main(int argc,char *argv[])
{
      ifstream inf1,inf2;
      ofstream outf;
      int Cu_n,CuZr_n,i,num;
      double Cu_xlo,Cu_xhi,Cu_ylo,Cu_yhi,Cu_zlo,Cu_zhi,
             CuZr_xlo,CuZr_xhi,CuZr_ylo,CuZr_yhi,CuZr_zlo,CuZr_zhi,
             xlo,xhi,ylo,yhi,zlo,zhi,x,y,z,c,d,d1,d2;
      double vx[MAX_ATOM],vy[MAX_ATOM],vz[MAX_ATOM];      

      string block;

      inf1.open("500K.dump");
      inf2.open("1000K.dump");
      outf.open("coexisting_Al.data");


      inf1>>block>>block;
      inf1>>block;
      inf1>>block>>block>>block>>block;
      inf1>>Cu_n;
      inf1>>block>>block>>block;
      inf1>>block>>block>>block;
      inf1>>Cu_xlo>>Cu_xhi;
      inf1>>Cu_ylo>>Cu_yhi;
      inf1>>Cu_zlo>>Cu_zhi;
      inf1>>block>>block>>block>>block>>block>>block>>block;
      inf1>>block>>block>>block;
     

      inf2>>block>>block;
      inf2>>block;
      inf2>>block>>block>>block>>block;
      inf2>>CuZr_n;
      inf2>>block>>block>>block;
      inf2>>block>>block>>block;

      inf2>>CuZr_xlo>>CuZr_xhi;
      inf2>>CuZr_ylo>>CuZr_yhi;
      inf2>>CuZr_zlo>>CuZr_zhi;
      inf2>>block>>block>>block>>block>>block>>block>>block;
      inf2>>block>>block>>block;

       cout<<"number of solid: "<<Cu_n<<endl;
       cout<<"xlo and xhi of solid:  "<<" "<<Cu_xlo<<"  "<<Cu_xhi<<endl;


       cout<<"number of liquid: "<<CuZr_n<<endl;
       cout<<"xlo and xhi of liquid:  "<<" "<<CuZr_xlo<<"  "<<CuZr_xhi<<endl;




 
      //normally we set d1=d2=0.0


      d=atof(argv[1]);
      d1=atof(argv[2]);
      d2=atof(argv[3]);
     
      xlo=Cu_xlo; xhi=Cu_xhi+2*d+CuZr_xhi-CuZr_xlo;
      ylo=min(Cu_ylo,CuZr_ylo)-d1;  yhi=max(Cu_yhi,CuZr_yhi)+d1;
      zlo=min(Cu_zlo,CuZr_zlo)-d2;  zhi=max(Cu_zhi,CuZr_zhi)+d2;
  
    outf<<"# Lammps Simulation"<<endl;
    outf<<endl;
    outf<<Cu_n+CuZr_n<<" atoms"<<endl;
    outf<<endl;
    outf<<"1 atom types"<<endl;
    outf<<endl;
    outf<<endl;
    outf<<endl;
    outf<<xlo<<" "<<xhi<<" xlo xhi"<<endl;
    outf<<ylo<<" "<<yhi<<" ylo yhi"<<endl;
    outf<<zlo<<" "<<zhi<<" zlo zhi"<<endl;
    outf<<endl;
    outf<<"Atoms"<<endl;
    outf<<endl;


     for(i=1;i<=Cu_n;i++)
        {
          inf1>>num;
          inf1>>c>>x>>y>>z>>vx[i]>>vy[i]>>vz[i];
          outf<<i<<" "<<c<<" "<<x<<" "<<y<<" "<<z<<endl;
        }

     int ii;
     for(i=1;i<=CuZr_n;i++)
        { ii=i+Cu_n;
          inf2>>num;
          inf2>>c>>x>>y>>z>>vx[ii]>>vy[ii]>>vz[ii];
          outf<<ii<<" "<<c<<" "<<x-CuZr_xlo+d+Cu_xhi<<" "<<y<<" "<<z<<endl;
        }

      outf<<endl;
      outf<<"Velocities"<<endl;
      outf<<endl;

      for (i=1;i<=Cu_n+CuZr_n;i++)
           outf<<i<<" "<<vx[i]<<" "<<vy[i]<<" "<<vz[i]<<endl;

     inf1.close();
     inf2.close();
     outf.close();
      return 0;
}

            
