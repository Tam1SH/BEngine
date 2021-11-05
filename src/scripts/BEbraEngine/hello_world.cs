using System;

namespace BEbraEngine
{
    class Pizda
    {
        public string pizda = "PIZDA";
    }

    public class BindingTest
    {
        static void sayhello()
        {
            Pizda d = null;
            var s = d.pizda;

            //throw new Exception("PIZDA");
        }
    }
}
