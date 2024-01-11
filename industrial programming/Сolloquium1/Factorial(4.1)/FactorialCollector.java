import java.util.ArrayList;
import java.util.List;
public class FactorialCollector {
    /**
     * Calculate first n factorials.
     * From 1 to n.
     *
     * @param upperBorder the upper limit for calculating factorials
     * @return a list of factorials from 1 to n
     * @throws IllegalArgumentException if the upperBorder is less than 0
     */
    public static List<Long> getFactorialRow(long upperBorder) {
        List<Long> factorialContainer = new ArrayList<>();

        if (upperBorder < 0) {
            throw new IllegalArgumentException();
        }

        for (int i = 1; i <= upperBorder; i++) {
            factorialContainer.add(getFactorial(i));
        }

        return factorialContainer;
    }

    private static long getFactorial(long n) {
        if (n < 0) {
            throw new IllegalArgumentException();
        }

        if (n == 0 || n == 1) {
            return 1;
        }

        return n * getFactorial(n - 1);
    }