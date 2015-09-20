#include "Simulation.h"


using namespace math;

void
Simulation::loadScene(float startX,float startY,float endX,float endY,int _x_bound,int _y_bound)
{
	startPosition = Vec2f(startX,startY);
	endPosition = Vec2f(endX,endY);

    x_bound = _x_bound;
    y_bound = _y_bound;

    cout<<"The grid is "<<x_bound<<" x "<<y_bound<<"\n";

}

bool
Simulation::frame()
{
    int status = flock.update();
	sleep(sleepTime);

    if(status)
        return true;
    else
        return false;
}


void
Simulation::init(

              	int 	mfishCount 			,
				float 	mdestWeight 		,
				int 	mrandSeed 			,
				float	msleepTime			,
              	int 	mboundaryPadding 	,
              	float 	mmaxSpeed 			,
              	float 	mmaxForce 			,
           		float 	mflockSepWeight 	,
           		float 	mflockAliWeight 	,
           		float 	mflockCohWeight 	,
           		float 	mcollisionWeight 	,
           		float 	mflockSepRadius 	,
           		float 	mflockAliRadius 	,
           		float 	mflockCohRadius 	,
				float	mstartPosRad		,
				float	mendPosRad

           		)

{


	sleepTime			= msleepTime		;
  	fishCount 			= mfishCount 		;
  	boundaryPadding 	= mboundaryPadding	;
  	maxSpeed 			= mmaxSpeed 		;
  	maxForce 			= mmaxForce 		;
	flockSepWeight 		= mflockSepWeight 	;
	flockAliWeight 		= mflockAliWeight 	;
	flockCohWeight 		= mflockCohWeight 	;
    collisionWeight 	= mcollisionWeight	;
	flockSepRadius 		= mflockSepRadius 	;
	flockAliRadius 		= mflockAliRadius 	;
	flockCohRadius 		= mflockCohRadius 	;
    destWeight 			= mdestWeight 		;
    randSeed 			= mrandSeed 		;
	startPositionRadius	= mstartPosRad		;
	endPositionRadius	= mendPosRad		;

    int startPosMinX = min((int)(startPosition.x-startPositionRadius),0);
    int startPosMaxX = min((int)(startPosition.x+startPositionRadius),(int)x_bound);
    int startPosMinY = min((int)(startPosition.y-startPositionRadius),0);
    int startPosMaxY = min((int)(startPosition.y+startPositionRadius),(int)y_bound);

    flock.setBounds(x_bound,y_bound);
    flock.setSimulationParameters(boundaryPadding	,
      			maxSpeed 		,
  				maxForce 		,
				flockSepWeight 	,
				flockAliWeight 	,
				flockCohWeight 	,
    			collisionWeight ,
				flockSepRadius 	,
				flockAliRadius 	,
				flockCohRadius 	,
    			destWeight		);

    flock.setDestination(endPosition,endPositionRadius);

    //flock.useCollisionSDF(true);
    //flock.calculatePartialDerivaties();

    int seed=randSeed;

	for(int i = 0; i < fishCount; ++i)
    {
        float rand_radius = (float)randomRange(0,(int)(startPositionRadius*100),seed+i*1324)/100;
        float theta = (float)randomRange(0,360,seed+i*4321);//Arbritary +1. just to change seed
        flock.addBoid(startPosition.x+rand_radius*cos(theta*PI/180),startPosition.y+rand_radius*sin(theta*PI/180));
        cout<<" \n x y :"<<startPosition.x+rand_radius*cos(theta*PI/180)<<" "<<startPosition.y+rand_radius*sin(theta*PI/180)<<"   rand radius: "<<rand_radius<<" theta "<<theta;
    }

}



void
Simulation::run()
{
	bool continueRunning = true;
	while (continueRunning) {

		continueRunning = frame();

	}

}


Flocking* Simulation::getFlockHandle()
{
        return &flock;
}

void Simulation::draw()
{
    flock.draw();
}
