using System;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.Linq;
using System.Xml.Schema;
using AI.SteeringBehaviors.Core;

namespace AI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        float avgPos = 0;
        float avgFor = 0;


        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }

        public float FlockRadius { get; set; }


        public Flock()
        {
            //  Vector3 avgPosit = AveragePosition;
            //Vector3 avgFore = null;
        }

        public virtual void Update(float deltaTime)
        {
            Vector3 averageFor = Vector3.Empty;

            for (int i = 0; i < Boids.Count; i++)
            {
                averageFor += Boids[i].Velocity;
            }

            averageFor = averageFor / Boids.Count;

            this.AverageForward = averageFor;

            Vector3 avgPos = Vector3.Zero;

            for (int i = 0; i < Boids.Count; i++)
            {
                avgPos += Boids[i].Position;
            }

            avgPos = avgPos / Boids.Count;

            this.AveragePosition = avgPos;

            float accel = 0;

            Vector3 final;
            for (int i = 0; i < this.Boids.Count; i++)
            {

                Vector3 allign = averageFor / Boids[i].MaxSpeed;
                if (allign.Length > 1)
                {
                    allign.Normalize();

                }
                allign = allign * AlignmentStrength;
                final = allign;
                Vector3 cohes = avgPos - Boids[i].Position;
                float dist = cohes.Length;
                cohes /= cohes.Length;

                if (dist < FlockRadius)
                {
                    cohes *= dist / FlockRadius;
                }
                cohes = cohes * CohesionStrength;
                final += cohes;

                Vector3 sum = Vector3.Empty;

                for (int j = 0; j < this.Boids.Count; j++)
                {

                    if (j != i)
                    {
                        Vector3 sep = this.Boids[i].Position - Boids[j].Position;
                        float separ = sep.Length;
                        float safeDist = this.Boids[i].SafeRadius + Boids[j].SafeRadius;

                        if (separ < safeDist)
                        {
                            sep /= sep.Length;
                            sep *= (safeDist - separ) / safeDist;
                            sum += sep;
                        }
                    }
                }
                if (sum.Length > 1.0f)
                {

                    sum.Normalize();
                }
                final += sum * SeparationStrength;

                float Mult = Boids[i].MaxSpeed;
                final *= Mult * deltaTime;

                Boids[i].Velocity += final;

                if (Boids[i].Velocity.Length > Boids[i].MaxSpeed)
                {
                    Boids[i].Velocity.Normalize();
                    Boids[i].Velocity *= Boids[i].MaxSpeed;
                }
                Boids[i].Update(deltaTime);
            }

            // Update goes here
        }

    }
}
