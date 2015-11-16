#include "Particle.h"
#include "Kinematics.h"
#include <iostream>


//using std::cout; using std::endl;

const double speed_of_light = 299792458;

void Particle_Generator::Generate_Particle(Particle &part){
	part.Set_Mass(mass_particle);
	double pmom, theta, pphi;
	dist->sample_momentum(pmom, theta, pphi);
	//std::cout << "pmom = " << pmom << " theta = " << theta << " phi = " << pphi << std::endl;
	part.ThreeMomentum(pmom*cos(pphi)*sin(theta), pmom*sin(pphi)*sin(theta), pmom*cos(theta));
}

Particle::Particle(double mass){
    Set_Mass(mass);
    ThreeMomentum(0,0,0);
    for(int i=0; i<4; i++){
        origin_coords[i]=0.0;
		end_coords[i]=0.0;
	}	
    EVENT_SET = false;
}

double Particle::Theta(){
    return calculatetheta(px, py, pz, E); 
}  

double Particle::Phi(){
    return phi(px, py, pz, E);
}

void Particle::FourMomentum(double PX, double PY, double PZ, double P0){

	px = PX;
	py = PY;
	pz = PZ;
	E = P0;
}

void Particle::ThreeMomentum(double PX, double PY, double PZ){
    
    px = PX;
    py = PY;
    pz = PZ;
    E = sqrt(m*m+px*px+py*py+pz*pz);

}

void Particle::Set_Mass(double m_new){
    m = m_new;
    E = sqrt(m_new*m_new+px*px+py*py+pz*pz);
}

void Particle::Set_Origin(double x, double y, double z){
	origin_coords[0]=x;
	origin_coords[1]=y;
	origin_coords[2]=z;
}

void Particle::Set_Position(double x, double y, double z){
    end_coords[0]=x;
    end_coords[1]=y;
    end_coords[2]=z;
}

void Particle::Set_Creation_Time(double t){
	origin_coords[3]=t;
}

void Particle::Set_Time(double t){
    end_coords[3]=t;
}

void Particle::Lorentz(Particle parent){
	
	double M1 = parent.m;	
	double E1 = parent.E;
	double p1x = parent.px;
	double p1y = parent.py;
	double p1z = parent.pz;
	double E2 = E;	
	double p2x = px;
	double p2y = py;
	double p2z = pz;
	double E3, p3x, p3y, p3z;		
	double gamma, v;	
	double vx, vy, vz;	
	double Lam11, Lam12, Lam13, Lam14;	
	double Lam21, Lam22, Lam23, Lam24;	
	double Lam31, Lam32, Lam33, Lam34;
	double Lam41, Lam42, Lam43, Lam44;	
    gamma = E1/M1;
    v = sqrt(1.0-1.0/gamma/gamma);
	if(v==0.0)
        return;
    vx = p1x/E1;
	vy = p1y/E1;
	vz = p1z/E1;
	Lam11 = gamma;
	Lam12 = gamma*vx;
	Lam13 = gamma*vy;
	Lam14 = gamma*vz;
	Lam21 = gamma*vx;
	Lam22 = 1+(gamma-1)*vx*vx/v/v;
	Lam23 = (gamma-1)*vx*vy/v/v;
	Lam24 = (gamma-1)*vx*vz/v/v;
	Lam31 = gamma*vy;
	Lam32 = (gamma-1)*vy*vx/v/v;
	Lam33 = 1+(gamma-1)*vy*vy/v/v;
	Lam34 = (gamma-1)*vy*vz/v/v;
	Lam41 = gamma*vz;
	Lam42 = (gamma-1)*vz*vx/v/v;
	Lam43 = (gamma-1)*vz*vy/v/v;
	Lam44 = 1+(gamma-1)*vz*vz/v/v;
	E3   = Lam11*E2+Lam12*p2x+Lam13*p2y+Lam14*p2z;	
	p3x  = Lam21*E2+Lam22*p2x+Lam23*p2y+Lam24*p2z;	
	p3y  = Lam31*E2+Lam32*p2x+Lam33*p2y+Lam34*p2z;	
	p3z  = Lam41*E2+Lam42*p2x+Lam43*p2y+Lam44*p2z;
		
	FourMomentum(p3x, p3y, p3z, E3);
}

void Particle::Rotate_x(double psi){
    double zr = pz*cos(psi)+py*sin(psi);
    double yr = py*cos(psi)-pz*sin(psi);
    pz = zr; py = yr;
}

void Particle::Rotate_y(double theta){
    double zr = pz*cos(theta)-px*sin(theta);
    double xr = px*cos(theta)+pz*sin(theta);
    px=xr; pz=zr;
}

void Particle::Rotate_z(double phi){
    double yr = py*cos(phi)+px*sin(phi);
    double xr = px*cos(phi)-py*sin(phi);
    px=xr; py=yr;
}

double Particle::Momentum(){
    return sqrt(px*px+py*py+pz*pz);
}
//Speed is in units of c
double Particle::Speed(){
    if(Momentum()==0.0)
        return 0.0;
    return Momentum()/E;
}

void Particle::Generate_Position(double rngpoint){
    Set_Position(px*rngpoint, py*rngpoint, pz*rngpoint);
    if(Momentum()==0.0){
        Set_Time(origin_coords[3]);
    }
    else{
        Set_Time(Momentum()*rngpoint/Speed()/speed_of_light+orgin_coords[3]);
    }
}

void Particle::report(std::ostream& ostr){
    ostr << name << " " << E << " " << px << " " << py << " " << pz << " " << m << std::endl;
}
