using System;

namespace C_
{
    class Telefoni
    {
        public static void Solve()
        {
            string[] input = Console.ReadLine().Split();
            int N = int.Parse(input[0]);
            int D = int.Parse(input[1]);
            input = Console.ReadLine().Split();
            int[] A = new int[N];
            for (int i = 0; i < N; ++i) 
                A[i] = int.Parse(input[i]);
        }
    }
}