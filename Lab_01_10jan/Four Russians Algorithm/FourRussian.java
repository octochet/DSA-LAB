import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class FourRussiansAlgorithm {

    public boolean[][] fourRussiansMultiply(boolean[][] aMatrix, boolean[][] bMatrix) {
        int n = aMatrix.length;

        if(n == 1) {
            boolean[][] C1 = new boolean[1][1];
            C1[0][0] = aMatrix[0][0] && bMatrix[0][0];
            return C1;
        }

        int m = (int) (Math.log(n) / Math.log(2));

        List<boolean[][]> aMatrixPartitioned = getColumnWisePartition(aMatrix, m, n);
        List<boolean[][]> bMatrixPartitioned = getRowWisePartition(bMatrix, m, n);

        boolean[][] cMatrix = new boolean[n][n];

        for (int i = 0; i < n/m; ++i) {
            boolean[][] rowSums = new boolean[(int) Math.pow(2, m)][n];
            int bp = 1, k = 0;
            for (int j = 1; j < Math.pow(2, m); ++j) {
                rowSums[j] = calculateRowSum(rowSums[j - (int) Math.pow(2, k)], getRowFromBottom(bMatrixPartitioned.get(i), k));

                if (bp == 1) {
                    bp = j + 1;
                    k++;
                } else {
                    bp--;
                }
            }

            boolean[][] ci = new boolean[n][n];
            for (int j = 0; j < n; ++j) {
                ci[j] = rowSums[getNum(aMatrixPartitioned.get(i)[j])];
            }

            cMatrix = matrixSum(cMatrix, ci);
        }
        return cMatrix;
    }

    private static boolean[] getRowFromBottom(boolean[][] array, int k) {
        return array[array.length - k - 1];
    }

    private static boolean[] calculateRowSum(boolean[] a, boolean[] b) {
        int size = a.length;
        boolean[] result = new boolean[size];

        for (int i = 0; i < size; ++i) {
            result[i] = a[i] || b[i];
        }

        return result;
    }

    private static List<boolean[][]> getColumnWisePartition(boolean[][] matrix, int m, int n) {
        List<boolean[][]> result = new ArrayList<>();

        for (int i = 0; i < n/m; ++i) {
            boolean[][] partition = new boolean[n][m];
            for (int col = 0; col < m; ++col) {
                boolean[] tmpColumn = getColumn(matrix, i * m + col);
                for (int row = 0; row < n; ++row) {
                    partition[row][col] = tmpColumn[row];
                }
            }
            result.add(partition);
        }
        return result;
    }

    private static List<boolean[][]> getRowWisePartition(boolean[][] matrix, int m, int n) {
        List<boolean[][]> result = new ArrayList<>();

        for (int i = 0; i < n/m; ++i) {
            boolean[][] partition = new boolean[m][n];
            for (int row = 0; row < m; ++row) {
                partition[row] = matrix[i * m + row];
            }
            result.add(partition);
        }

        return result;
    }

    private static boolean[] getColumn(boolean[][] array, int index) {
        int size = array.length;
        boolean[] column = new boolean[size];

        for (int i = 0; i < size; ++i)
            column[i] = array[i][index];

        return column;
    }

    private static int getNum(boolean[] row) {
        int num = 0;
        int size = row.length - 1;

        for (int i = 0; i <= size; ++i) {
            if (row[i]) {
                num += Math.pow(2, i);
            }
        }
        return num;
    }

    private static boolean[][] matrixSum(boolean[][] a, boolean[][] b) {
        int n = a.length;
        boolean[][] result = new boolean[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = a[i][j] || b[i][j];
            }
        }

        return result;
    }
}

public class FourRussian {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter dimension of square matrix, n = ");
        int n = sc.nextInt();
        boolean[][] a = new boolean[n][n];
        boolean[][] b = new boolean[n][n];
        boolean[][] c = new boolean[n][n];
        boolean[][] d = new boolean[n][n];
        System.out.println("Enter A matrix :");
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int x = sc.nextInt();
                boolean bool = (x==1);
                a[i][j] = bool;
            }
        }
        System.out.println("Enter B matrix :");
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int x = sc.nextInt();
                boolean bool = (x==1);
                b[i][j] = bool;
            }
        }
        sc.close();
        FourRussiansAlgorithm fr = new FourRussiansAlgorithm();
        long frstart = System.nanoTime();
        c = fr.fourRussiansMultiply(a, b);
        long frend = System.nanoTime();
        System.out.println("C=A*B matrix by Four Russians method :");
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int x = 0;
                if(c[i][j]) {
                    x=1;
                }
                System.out.print(x+" ");
            }
            System.out.print("\n");
        }
        long frexecution = frend - frstart;
        System.out.println("The total execution time was = "+ frexecution +" nanoseconds");

        System.out.println("C=A*B matrix by matrix multiplication :");
        long start = System.nanoTime();
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                d[i][j] = false;
                for(int k=0; k<n; k++) {
                    d[i][j] |=a[i][k] && b[k][j];
                }
            }
        }
        long end = System.nanoTime();
        long execution = end - start;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int x = 0;
                if(d[i][j]) {
                    x=1;
                }
                System.out.print(x+" ");
            }
            System.out.print("\n");
        }
        System.out.println("The total execution time was = "+ execution +" nanoseconds");
        double speedup = (double)execution/(double)frexecution;
        System.out.println("Total Speedup = " + speedup);
    }
}
