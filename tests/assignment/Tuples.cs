class Samples
{
    public static double StandardDeviation(IEnumerable<double> sequence)
    {
        (int count, double sum, double sumOfSquares) = ComputeSumAndSumOfSquares(sequence);
        var (sum, sumOfSquares, count) = ComputeSumAndSumOfSquares(sequence);
        (double sum, var sumOfSquares, var count) = ComputeSumAndSumOfSquares(sequence);

        var variance = sumOfSquares - sum * sum / count;
        return Math.Sqrt(variance / count);
    }

    public class Point
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int x, int y) => (X, Y) = (x, y);
    }
}
