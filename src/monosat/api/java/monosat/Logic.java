package monosat;
import monosat.MonosatJNI;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;

/**
 * Logic provides static accessors for common logic functions.
 * It also provides a  (thread local) static solver instance (getSolver()),
 * and some methods for accessing and replacing that solver instance.
 *
 * The expected use of Logic is for all methods of Logic to be statically imported:
 * import static monosat.Logic.*
 * Making these static methods available as a light-weight domain specific language.
 */
public final class Logic {
    private static final ThreadLocal<Solver> _solver = new ThreadLocal();

    private Logic(){

    }

    public static Solver newSolver(){
        setSolver(new Solver());
        return getSolver();
    }

    public static Solver newSolver(String args){
        setSolver(new Solver(args));
        return getSolver();
    }
    public static void setSolver(Solver s){
        _solver.set(s);
    }

    public static Solver getSolver(){
        if (_solver.get() == null){
            newSolver();
        }
        return _solver.get();
    }

    public static Lit newLit(){
        return newLit(true);
    }
    public static Lit newLit(boolean decidable){
        return getSolver().newLit(decidable);
    }

    //Note: True and False are capitalized here, to avoid name clashing with 'true' and 'false'
    public static Lit True(){
        return getSolver().getTrue();
    }
    public static Lit False(){
        return getSolver().getFalse();
    }
    public static boolean solve(){
        return getSolver().solve();
    }

    public static boolean solve(Lit...assumptions){
        return getSolver().solve(assumptions);
    }

    public static boolean solve(Collection<Lit> assumptions){
        return getSolver().solve(assumptions);
    }


    //Literal level constructs
    public static Lit ite(Lit condition, Lit then,Lit els){
        Solver solver = getSolver();
        return solver.ite(condition, then,els);
    }

    public static Lit and(Lit ... args){
        return getSolver().and(args);
    }
    public static Lit or(Lit... args){
        return getSolver().or(args);
    }
    public static Lit not(Lit a){
        //don't need the solver for this call
        //so avoid the thread local access of using getSolver()
        return a.negate();
    }
    public static Lit nand(Lit...args){
        return getSolver().nand(args);
    }
    public static Lit nor(Lit...args){
        return getSolver().nor(args);
    }
    public static Lit xor(Lit...args){
        return getSolver().xor(args);
    }
    public static Lit xnor(Lit...args){
        return getSolver().xnor(args);
    }

    //Assertion forms.
    public static void assertTrue(Lit a){
        getSolver().assertTrue(a);
    }
    public static void assertFalse(Lit a){
        getSolver().assertFalse(a);
    }

    public static void assertAnd(Lit...args){
        getSolver().assertAnd(args);
    }
    public static void assertOr(Lit...args){
        getSolver().assertOr(args);
    }

    public static void assertNand(Lit...args){
        getSolver().assertNand(args);
    }
    public static void assertNor(Lit...args){
        getSolver().assertNor(args);
    }
    public static void assertXor(Lit...args){
        getSolver().assertXor(args);
    }
    public static void assertXnor(Lit...args){
        getSolver().assertXnor(args);
    }
    public static void assertEqual(Lit a, Lit b){
        getSolver().assertEqual(a,b);
    }

    //Multi-Literal constructs
    public static Lit and(Collection<Lit> elements){
       return getSolver().and(elements);
    }
    public static Lit or(Collection<Lit> elements){
        return getSolver().or(elements);
    }
    public static Lit nand(Collection<Lit> elements){
        return getSolver().nand(elements);
    }
    public static Lit nor(Collection<Lit> elements){
        return getSolver().nor(elements);
    }
    public static Lit xor(Collection<Lit> elements){
        return getSolver().xor(elements);
    }
    public static Lit xnor(Collection<Lit> elements){
        return getSolver().xnor(elements);
    }

    //assertion forms
    public static void assertAnd(Collection<Lit> elements){
        getSolver().assertAnd(elements);
    }
    public static void assertOr(Collection<Lit> elements){
        getSolver().assertOr(elements);
    }
    public static void assertNand(Collection<Lit> elements){
        getSolver().assertNand(elements);
    }
    public static void assertNor(Collection<Lit> elements){
        getSolver().assertNor(elements);
    }
    public static void assertXor(Collection<Lit> elements){
        getSolver().assertXor(elements);
    }
    public static void assertXnor(Collection<Lit> elements){
        getSolver().assertXnor(elements);
    }


    //Bitvector constructs
    public static BitVector ite(Lit condition, BitVector then, BitVector els){
        return getSolver().ite(condition,then,els);
    }
    public static BitVector and(BitVector a, BitVector b){
        return getSolver().and(a,b);
    }
    public static BitVector or(BitVector a, BitVector b){
        return getSolver().or(a,b);
    }
    public static BitVector not(BitVector a){
        return getSolver().not(a);
    }
    public static BitVector nand(BitVector a, BitVector b){
        return getSolver().nand(a,b);
    }
    public static BitVector nor(BitVector a, BitVector b){
        return getSolver().nor(a,b);
    }
    public static BitVector xor(BitVector a, BitVector b){
        return getSolver().xor(a,b);
    }
    public static BitVector xnor(BitVector a, BitVector b){
        return getSolver().xnor(a,b);
    }

    public static BitVector add(BitVector a, BitVector b){
        return getSolver().add(a,b);
    }
    public static BitVector subtract(BitVector a, BitVector b){
        return getSolver().subtract(a,b);
    }

    public static void assertEqual(BitVector a, BitVector b){
        getSolver().assertEqual(a,b);
    }

    public static void assertEqual(BitVector a, long constant){
        getSolver().assertEqual(a,constant);
    }
    public static void assertEqual(long constant,BitVector a){
        getSolver().assertEqual(constant,a);
    }
    public static BitVector min(Collection<BitVector> args){
        return getSolver().min(args);
    }
    public static BitVector min(BitVector a, BitVector b){
        return getSolver().min(a,b);
    }
    public static BitVector max(Collection<BitVector> args){
        return getSolver().max(args);
    }
    public static BitVector max(BitVector a, BitVector b){
        return getSolver().max(a,b);
    }

    /**
     * Create a new bitvector  of the specified width, with a constant value
     * @param width
     * @param constant
     * @return
     */
    public static BitVector bv(int width, long constant){
        return getSolver().bv(width,constant);
    }

    /**
     * Create a new bitvector of the specified width.
     * @param width
     * @return
     */
    public static BitVector bv(int width){
        return new BitVector(getSolver(),width);
    }
}
