using System;

namespace C_
{
    class TimeOnTask
    {
        public static void Solve()
        {
            int T = Convert.ToInt32(Console.ReadLine());
            int C = Convert.ToInt32(Console.ReadLine());
            int[] A = new int[C];
            for (int i = 0; i < C; ++i)
            {
                A[i] = Convert.ToInt32(Console.ReadLine());
            }
            Array.Sort(A);
            int currentSum = 0;
            for (int i = 0; i < C; ++i)
            {
                currentSum += A[i];
                if (currentSum > T)
                {
                    Console.WriteLine(i);
                    return;
                }
            }
            Console.WriteLine(C);
        }
    }
}
