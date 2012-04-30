#ifndef SOLVER_H
#define SOLVER_H

#include "Globals.h"
#include "body.h"

#define max_conts 100
#define timestep 1
typedef std::vector<Body> domain; //  all the balls in the current processor

//void find_contact(domain &bodies,vector<pair<int,int> > &allcontacts)

/* 
 * In this way for the vector3 allcontacts, the first one is the body id, the second one is the second body id
 * the third one is the contactid
 */

void find_contact(domain &bodies,vector<int> &allcontacts, vd &psi)
{
	int i, j, contactid=0;
	vector3 pos1, pos2;
	vector3 contact[max_conts];
	float dist;

	REP(i, 0, retain)
	{
		REP(j, i+1, retain)
		{
			pos1 = body[i].get_position();
			pos2 = body[j].get_position();
            dist = norml(pos1 - pos2);

			if(dist - radius*2 < 1E-6)
			{
				psi.push_back(dist - radius*2);
				allcontacts[contactid].push_back(i);
				allcontacts[contactid].push_back(j);
				allcontacts[contactid].push_back(contactid);
				contactid ++;
			}

		}

		
	}
	
}

void construct_gn(const Body &b1,const Body &b2,vd &gn)
{
	vector3 gn1, gn2, gn1_norm, gn2_norm;
	gn1 = b1.get_position() - b2.get_position();
	gn1_norm = gn1.Normalize(gn1);
	
	gn2_norm = - gn1_norm;
	REP(i,0,3){gn.push_back(gn1_norm[i]);}
	REP(i,0,3){gn.push_back(0);          }
	REP(i,0,3){gn.push_back(gn2_norm[i]);}
	REP(i,0,3){gn.push_back(0);          }
	
}


void construct_ext(const Body &b1,const Body &b2,vd &ext)
{
	vector3 ext1, ext2;
	ext1 = b1.get_ext() 
	ext2 = b2.get_ext();
	
	REP(i,0,3) {ext.push_back(ext1[i];     }
	REP(i,0,3) {ext.push_back(0);          }
	REP(i,0,3) {ext.push_back(ext2[i]);    }
	REP(i,0,3) {ext.push_back(0);          }
}


void construct_vel(const Body &b1,const Body &b2,vd &vel)
{
	vector3 vel1, vel2;
	ext1 = b1.get_ext(); 
	ext2 = b2.get_ext();
	
	REP(i,0,3){ext.push_back(ext1[i];     }
	REP(i,0,3){ext.push_back(0);          }
	REP(i,0,3){ext.push_back(ext2[i]);    }
	REP(i,0,3){ext.push_back(0);          }

}


void construct_velPlusOne(const vd &mass,const vd&ext,const vd &vel, double &pnPlusOne, const vd &gn, vd &velPlusOne, const int &contactid, const vd &psi)
{
   /*
	*velPlusOne = vel + gn/m * pnPlusOne + gf/mass*pfPlusOne + ext/mass;
	*/
   
   double pn_star, r=0.5, rho_n;
   vd gn_mass;
   vd ext_mass;
   gn_mass = 1/mass * gn * pnPlusOne;  // [12] * [1]
   ext_mass = 1/mass * ext;
   velPlusOne = vel + gn_mass + ext_mass;

   rho_n = psi[contactid] / timestep + gn*velPlusOne;
   pn_star = pnPlusOne - r * rho_n;
   if (pn_star < 0)
   {
	   pn_star = 0;
   }

}

void construct_mass(const Body &b1,const Body &b2,vd &mass)
{
    double m1,i2,m2,i2;
    m1 = b1.get_mass();
    m2 = b2.get_mass();
    i1 = b1.get_inertia();
    i2 = b1.get_inertia();
    REP(i,0,3) { mass.push_back(m1);   }
    REP(i,0,3) { mass.push_back(i1);   }
    REP(i,0,3) { mass.push_back(m2);   }
    REP(i,0,3) { mass.push_back(i2);   }
}

void iterative_step(double psi,const vd &gn,const vd &velPlusOne,vd &pnPlusOne)
{
    // initialize pnPlusOne
    // TODO : pnPlusOne is a double not a vector of doubles
    vd prev;
    while(true)
    {
        if(is_converged(prev,pnPlusOne))
            break;
        update(pnPlusOne);
        prev.clear();
        prev.insert(all(pPlusOne));
    }
}

/*****
void prox(vd &pPlusOne)
{
    if(!is_greater_zero(pPlusOne))
        // make all the values 0
}
*******/


void pair_solver(Body &b1,Body &b2)
{
    /* Update the information for these bodies
     * */
    // Step 1 : Construct the three vectors corresponding to Mass, External Force and the velocity
    vd mass,ext,vel,gn,velPlusOne;
    double psi,pPlusOne;

    construct_mass(b1,b2,mass);
    construct_ext(b1,b2,ext);
    construct_vel(b1,b2,vel);
    construct_gn(b1,b2,gn);
    construct_velPlusOne(mass,ext,vel,gn,velPlusOne);
    psi = compute_psi(b1,b2);
    iterative_step(psi,gn,velPlusOne,pPlusOne);
//    return prox(pPlusOne);
}
void solve(domain &bodies)
{
    /*
     * Solve the forces and the velocities for the local and foreign bodies
     */
    double pPlusOne;
    map<int,vd > table;
    vector<pair<int,int > > contacts;
    find_contact(bodies,contacts);
    tr(contacts,it)
    {
       pPlusOne = pair_solver(bodies[it->first],bodies[it->second]);
       if(body1 in my domain)
       table[bodies[it->first]].push_back(pPlusOne);
       if(body2 in my domain)
       table[bodies[it->second]].push_back(pPlusOne);

    }
    // update the velocity
    tr(table,it)
    {
        // update the velocity of the body with the index it->first
    }
}
#endif
