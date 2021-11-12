using BEbraEngine;
using System;
using System.Runtime.CompilerServices;

namespace BEbraEngine
{
    class Pizda
    {
        public string pizda = "PIZDA";
    }
    public class Vector3
    {
        public float x;
        public float y;
        public float z;
        public Vector3() { }
        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public Vector3(float x, float y)
        {
            this.x = x;
            this.y = y;

        }
        public Vector3(float all)
        {
            x = all; 
            y = all;
            z = all;

        }
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static Vector3 operator +(Vector3 other, Vector3 dather);
    }


    class GameObject {

        GameObject() { }
        public static GameObject New(Vector3 position)
        {
            return new GameObject();
        }

    }

    public class BindingTest
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static string PoshelNaxyu();
        static void sayhello1()
        {

            Console.WriteLine(PoshelNaxyu());
            try
            {
                Vector3 pos = new Vector3(3,6,8);
                Vector3 pos1 = new Vector3(1,9,2);
                var posx = pos + pos1;
                Console.WriteLine(posx.x);
              //  var obj = GameObject.New(pos);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }


        }
    }
}
