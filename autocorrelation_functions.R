SimulateSimpleMarkovChain <- function(num_points=10000)
{
  t11 <- 0.999
  t22 <- 0.998 ## 
  curr_state <- 1
  
  state_sequence <- array(0,dim=c(num_points))
  obs_sequence <- array(0,dim=c(num_points))
  
  t <- array(0,dim=c(2,2))
  mus <- array(0,dim=c(2))
  sigmas <- array(0,dim=c(2))
  
  mus<-c(2.0,5.0)
  sigmas <- c(0.8,0.8)
  
  for(i in 1:num_points)
  {
    
    state_sequence[i] <- curr_state
    obs_sequence[i] <- rnorm(n=1,mean=mus[curr_state],sd=sigmas[curr_state])
    curr_state <- sample.int(n=2,size=1,prob=trans[curr_state,])
  }
  return(obs_sequence)
}

Plot_Langevin_Oscillator_Autocorrelation <- function()
{
  pi <- 3.1415926
  eta <- 0.89e-3 # dynamic viscosity of water at 25°C
  Temp <- 298.15
  kB <- 1.38e-23
  Radius <- 500e-9
  gamma <- 6*pi*eta*Radius
  k_eff <- 1.5e-4  ## effective trap stiffness in N/m
  density_silica <- 2.65e6 ## density of silica in g/m^3 (2.65 t / m^3)
  m <- 4/3*Radius^3*pi*density_silica
  print("mass of silica bead (in kg):")
  print(m)
  omega0_2 <- k_eff/m
  omega1 <- sqrt(omega0_2-gamma^2/(4*m^2))
  variance_x0 <- (kB*Temp)/(m*omega0_2)
  stdev_x0 <- sqrt(variance_x0)
  
  print(variance_x0)
  print(stdev_x0)  
  ## plot autocorrelation for a range of 0.05 ms to 10 ms
  
  npnts <- 25
  times <- seq(from=5e-5,to=0.00125,length=npnts)
  acf_signal <- array(0,dim=c(length(times)))
  for(i in 1:length(acf_signal))
  {
    acf_signal[i] <- exp(-gamma*times[i]/(2*m))*(cos(omega1*times[i])+(gamma/(2*m*omega1))*sin(omega1*times[i]))
  }
  autocorr_time <- 2*m/gamma
  print("autoccorrelation time: ")
  print(autocorr_time)
  
  plot(times,acf_signal)
}
