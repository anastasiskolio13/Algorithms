using System;
//using System.Reflection.PortableExecutable;
//using System.Runtime.Serialization.Formatters;

namespace C_
{
    struct segment
    {
        int L;
        int R;
    }

    class CarHoppers
    {
        public static void Solve()
        {
            for (int testcase = 0; testcase < 5; ++testcase)
            {
                string[] input = Console.ReadLine().Split();
                int N = int.Parse(input[0]);
                int M = int.Parse(input[1]);
                int[] A = new int[N];
                for (int i = 0; i < N; ++i)
                {
                    A[i] = Convert.ToInt32((Console.ReadLine()));
                }

            }
        }
    }
}
