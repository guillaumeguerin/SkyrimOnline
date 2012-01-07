using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SkyNet.SkyrimOnline.System
{
    public class WorkQueue: Queue<Job>
    {
        uint _threadCount;
        Thread[] _threads;
        public WorkQueue(uint ThreadCount = 1)
        {
            _threads = new Thread[_threadCount = ThreadCount];
            for (int i = 0; i < ThreadCount; i++)
                _threads[i] = new Thread(Run);
        }
        ~WorkQueue()
        {
            for (int i = 0; i < _threadCount; i++)
                _threads[i].Abort();
        }
        void Run()
        {
            Job _job;
            while (true)
            {
                lock (this)
                {
                    if (Count > 0)
                        _job = this.Dequeue();
                    else
                        _job = null;
                }
                if (_job != null)
                    _job.Work();
                else
                    Thread.Sleep(0);
            }
        }
    }
}
