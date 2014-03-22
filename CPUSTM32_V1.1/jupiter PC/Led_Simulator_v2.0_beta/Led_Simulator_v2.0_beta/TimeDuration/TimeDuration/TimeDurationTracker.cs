using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using Led_Simulator_v2._0_beta;

namespace Led_Simulator_v2._0_beta
{
    public class TimeDurationTracker : IObservable<TimeDuration>
    {
        public TimeDurationTracker()
        {
            observers = new List<IObserver<TimeDuration>>();
        }

        private List<IObserver<TimeDuration>> observers;

        public IDisposable Subscribe(IObserver<TimeDuration> observer)
        {
            if (!observers.Contains(observer))
                observers.Add(observer);
            return new Unsubscriber(observers, observer);
        }

        private class Unsubscriber : IDisposable
        {
            private List<IObserver<TimeDuration>> _observers;
            private IObserver<TimeDuration> _observer;

            public Unsubscriber(List<IObserver<TimeDuration>> observers, IObserver<TimeDuration> observer)
            {
                this._observers = observers;
                this._observer = observer;
            }

            public void Dispose()
            {
                if (_observer != null && _observers.Contains(_observer))
                    _observers.Remove(_observer);
            }
        }

        public void TrackTimeDuration(TimeDuration timeDuration)
        {
            foreach (var observer in observers)
            {
                if (timeDuration == null)
                    observer.OnError(new TimeDurationUnknownException());
                else
                    observer.OnNext(timeDuration);
            }
        }

        public void EndTransmission()
        {
            foreach (var observer in observers.ToArray())
                if (observers.Contains(observer))
                    observer.OnCompleted();

            observers.Clear();
        }

        public class TimeDurationUnknownException : Exception
        {
            internal TimeDurationUnknownException()
            { }
        }
    }
}
