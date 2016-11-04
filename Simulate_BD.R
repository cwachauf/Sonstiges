SimulateBDPath <- function()
{
  ## define some constants..:
  Temp <- 298.15
  kB <- 1.38e-23
  R <- 500e-9 ## 500 nm bead radius
  pi <- 3.14159
  
  eta <- 0.89e-03 ## dynamic viscosity of water
  gamma_s <- 6.0*pi*eta*R
  k_eff <- 3.5e-04 ## in N/m
  dt <- 1e-8 ## 10ns - timestep...
  
  Npnts <- 3000000
  xs <- array(0,dim=c(Npnts))
  xs_thinned <- array(0,dim=c(Npnts/5000))
  for(i in 2:Npnts)
  {
     xs[i] <- xs[i-1] + dt/gamma_s*(-k_eff*xs[i-1]+sqrt(2.0*kB*Temp*gamma_s/dt)*rnorm(n=1,mean=0,sd=1))
     xs[i] <- xs[i-1] + dt/gamma_s*(-k_eff*xs[i-1]+sqrt(2.0*kB*Temp*gamma_s/dt)*rnorm(n=1,mean=0,sd=1))
     if(i%%500==0)
     {
       xs_thinned[i/5000]=xs[i]
     }
  }
  return(xs_thinned)
}