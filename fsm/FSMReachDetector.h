/****************************************************************************************[Solver.h]
 The MIT License (MIT)

 Copyright (c) 2014, Sam Bayless

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **************************************************************************************************/
#ifndef FSM_REACHDETECTOR_H_
#define FSM_REACHDETECTOR_H_
#include "utils/System.h"

#include "dgl/DynamicGraph.h"

#include "DynamicFSM.h"

#include "core/SolverTypes.h"
#include "mtl/Map.h"


#include "utils/System.h"
#include "FSMDetector.h"
#include "alg/NFAReach.h"

using namespace dgl;
namespace Monosat {

class FSMTheorySolver;

class FSMReachDetector: public FSMDetector {
public:
	FSMTheorySolver* outer;
	DynamicFSM &g_under;
	DynamicFSM &g_over;

	int within;
	int source;
	vec<vec<int>> & strings;
	double rnd_seed;

	struct ReachStatus {
		FSMReachDetector & detector;
		bool polarity;
		void reaches(int string, int state,int edgeID,int label);

		ReachStatus(FSMReachDetector & _outer, bool _polarity) :
				detector(_outer), polarity(_polarity) {
		}
	};


	NFAReach<ReachStatus> * underapprox_detector;
	NFAReach<ReachStatus> * overapprox_detector;

	CRef underprop_marker;
	CRef overprop_marker;

	struct Change {
		Var v;
		int u;
		int str;
	};
	vec<bool> is_changed;
	vec<Change> changed;

	vec<vec<Lit>> reach_lits;
	Var first_reach_var;
	struct ReachLit{
		int str;
		int to;
	};
	vec<ReachLit> reach_lit_map;
	//stats
	
	int stats_full_updates = 0;
	int stats_fast_updates = 0;
	int stats_fast_failed_updates = 0;
	int stats_skip_deletes = 0;
	int stats_skipped_updates = 0;
	int stats_num_skipable_deletions = 0;
	int stats_learnt_components = 0;
	int stats_learnt_components_sz = 0;
	double mod_percentage = 0.2;
	int stats_pure_skipped = 0;
	int stats_shrink_removed = 0;
	double stats_full_update_time = 0;
	double stats_fast_update_time = 0;


	ReachStatus *underReachStatus = nullptr;
	ReachStatus *overReachStatus = nullptr;

	void printStats() {
		//printf("Reach detector\n");
		FSMDetector::printStats();
		if (opt_detect_pure_theory_lits)
			printf("\tPropagations skipped by pure literal detection: %d\n", stats_pure_skipped);
		if (opt_shrink_theory_conflicts) {
			printf("\t%d lits removed by shrinking conflicts\n", stats_shrink_removed);
		}
		if (opt_learn_unreachable_component) {
			printf("\t%d components learned, average component size: %f\n", stats_learnt_components,
					stats_learnt_components_sz / (float) stats_learnt_components);
		}
	}
	
	void unassign(Lit l) {
		FSMDetector::unassign(l);
		int index = indexOf(var(l));
		if (index >= 0 && index < reach_lit_map.size() && reach_lit_map[index].to != -1) {
			int node = reach_lit_map[index].to;
			int str =  reach_lit_map[index].str;
			if (!is_changed[index]) {
				changed.push( { var(l), node,str });
				is_changed[index] = true;
			}
		}
	}
	
	inline int indexOf(Var v)const{
		int index = v - first_reach_var;
		assert(index < reach_lit_map.size());
		return index;
	}

	int getState(Var reachVar) {
		assert(reachVar >= first_reach_var);
		int index = indexOf(reachVar);

		assert(reach_lit_map[index].to >= 0);
		return reach_lit_map[index].to;
	}
	int getString(Var reachVar) {
		assert(reachVar >= first_reach_var);
		int index = indexOf(reachVar);

		assert(reach_lit_map[index].to >= 0);
		return reach_lit_map[index].str;
	}

	bool propagate(vec<Lit> & conflict);
	void buildReachReason(int node,int str, vec<Lit> & conflict);
	void buildNonReachReason(int node,int str, vec<Lit> & conflict);

	void buildReason(Lit p, vec<Lit> & reason, CRef marker);
	bool checkSatisfied();
	void printSolution(std::ostream& write_to);

	void addReachLit(int state, int strID, Var reach_var);



	FSMReachDetector(int _detectorID, FSMTheorySolver * _outer, DynamicFSM &g_under, DynamicFSM &g_over,
			int _source, vec<vec<int>> &  strs, double seed = 1);
	virtual ~FSMReachDetector() {
		
	}
	
	const char* getName() {
		return "NFA Reachability Detector";
	}
	
	

};
}
;
#endif /* REACHDETECTOR_H_ */
