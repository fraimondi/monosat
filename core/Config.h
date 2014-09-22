/*
 * Config.h
 *
 *  Created on: 2012-10-20
 *      Author: sam
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "utils/Options.h"
#include "utils/System.h"
namespace Minisat {
extern IntOption opt_verb;
extern  DoubleOption  opt_var_decay;
extern  DoubleOption  opt_clause_decay ;
extern  DoubleOption  opt_random_var_freq ;
extern  DoubleOption  opt_random_seed;
extern  IntOption     opt_ccmin_mode  ;
extern  IntOption     opt_phase_saving ;
extern  BoolOption    opt_rnd_init_act ;
extern  BoolOption    opt_luby_restart ;
extern  IntOption     opt_restart_first ;
extern  DoubleOption  opt_restart_inc   ;
extern  DoubleOption  opt_garbage_frac  ;
extern  BoolOption    opt_rnd_restart ;

extern  DoubleOption  opt_random_theory_freq ;

extern  BoolOption opt_interpolate;
extern IntOption opt_eager_prop;
extern IntOption opt_subsearch;

extern BoolOption opt_graph;
extern BoolOption opt_inc_graph;
extern IntOption opt_dec_graph;
extern BoolOption opt_conflict_shortest_path;
extern BoolOption opt_conflict_min_cut;
extern IntOption opt_restrict_decisions;

extern StringOption opt_min_cut_alg;
extern StringOption opt_reach_alg;
extern StringOption opt_con_alg;
extern StringOption opt_allpairs_alg;
extern StringOption opt_undir_allpairs_alg;
extern StringOption opt_dist_alg;
extern StringOption opt_mst_alg;

extern StringOption opt_components_alg;
extern BoolOption opt_check_solution;
extern BoolOption opt_print_reach;
extern BoolOption opt_print_graph;

extern IntOption opt_learn_reaches;
extern StringOption opt_priority;

extern BoolOption opt_print_conflicts;
extern BoolOption opt_rnd_phase;
extern BoolOption opt_init_rnd_phase;

extern BoolOption opt_reach_prop;
extern BoolOption opt_decide_graph;
extern BoolOption opt_decide_graph_distance;
extern BoolOption opt_use_random_path_for_decisions;
extern BoolOption opt_use_optimal_path_for_decisions;
extern DoubleOption opt_decide_graph_re_rnd;
extern BoolOption opt_print_decision_path;
extern BoolOption opt_force_distance_solver;
extern DoubleOption opt_allpairs_percentage;
extern BoolOption opt_decide_graph_neg;
extern BoolOption opt_decide_graph_pos;
extern BoolOption opt_ignore_theories;
extern BoolOption opt_check_pure_theory_lits;
extern BoolOption opt_mst_min_cut;
extern BoolOption opt_connected_components_min_cut;
extern BoolOption opt_optimize_mst;
extern BoolOption opt_skip_deletions;
extern BoolOption opt_skip_additions;
extern BoolOption opt_permanent_theory_conflicts;
extern IntOption opt_temporary_theory_conflicts;
extern IntOption opt_temporary_theory_reasons;
extern BoolOption opt_force_directed;
extern BoolOption opt_decide_graph_chokepoints;
extern IntOption opt_sort_graph_decisions;
extern BoolOption  opt_rnd_order_graph_decisions;
extern BoolOption opt_compute_max_distance;
 extern BoolOption opt_detect_pure_theory_lits;
 extern BoolOption opt_detect_pure_lits;
 extern BoolOption opt_propagate_theories_during_simplification;
 extern BoolOption opt_shrink_theory_conflicts;
extern BoolOption opt_early_theory_prop;
 extern IntOption    opt_width;
 extern    IntOption    opt_height;
 extern   IntOption    opt_bits;
extern BoolOption opt_encode_reach_underapprox_as_sat;
 extern   BoolOption	 opt_csv;
 extern BoolOption opt_rnd_shuffle;
extern BoolOption opt_components_learn_connect;
extern BoolOption opt_learn_unreachable_component;
extern BoolOption opt_dinics_recursive;
extern StringOption opt_hull_alg;
extern StringOption opt_convex_pip;



enum class PointInPolygonAlg{
	 ALG_FULL,
	 ALG_RECURSIVE_SPLIT
};
extern PointInPolygonAlg pipalg;

enum class ReachAlg{
	 ALG_SAT,
	 ALG_DFS,
	 ALG_DIJKSTRA,
	 ALG_DISTANCE,
	 ALG_BFS,
	 ALG_RAMAL_REPS
};

//For undirected reachability
enum class ConnectivityAlg{
	 ALG_SAT,
	 ALG_DFS,
	 ALG_DIJKSTRA,
	 ALG_DISTANCE,
	 ALG_BFS,
	 ALG_THORUP
};
extern ConnectivityAlg undirectedalg;
extern ReachAlg reachalg;

enum class AllPairsAlg{
	 ALG_FLOYDWARSHALL,
	 ALG_DIJKSTRA_ALLPAIRS
};
extern AllPairsAlg allpairsalg;
enum class AllPairsConnectivityAlg{
	 ALG_FLOYDWARSHALL,
	 ALG_DIJKSTRA_ALLPAIRS,
	 ALG_THORUP
};
extern AllPairsConnectivityAlg undirected_allpairsalg;
enum class MinCutAlg{
	 ALG_EDMONSKARP,
	 ALG_EDKARP_ADJ,
	 ALG_IBFS,
	 ALG_EDKARP_DYN,
	 ALG_DINITZ,
	 ALG_DINITZ_LINKCUT
};
extern MinCutAlg mincutalg;
enum class MinSpanAlg{
	 ALG_KRUSKAL,
	 ALG_PRIM,
	 ALG_SPIRA_PAN
};
extern MinSpanAlg mstalg;
enum class ComponentsAlg{
	ALG_DISJOINT_SETS

};
extern ComponentsAlg componentsalg;

enum class ConvexHullAlg{
	ALG_MONOTONE_HULL,
	ALG_QUICKHULL

};
extern ConvexHullAlg hullAlg;

enum class DistAlg{
	 ALG_SAT,
	 ALG_DIJKSTRA,
	 ALG_DISTANCE,
	 ALG_RAMAL_REPS
};


extern DistAlg distalg;

extern IntOption opt_time;

static inline double rtime(int level=1){
	if(level<=opt_time){
		return cpuTime();
	}else{
		return 0;
	}
}

}

#endif /* CONFIG_H_ */
