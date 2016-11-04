AR_one_model <- function()
{
  phi <- 0.8825
  sigma_eps <- 0.5152
  c <- 0.5875155
  
  npnts <- 50000
  xs <- array(0,dim=c(npnts))
  
  ## set first point to mean value
  xs[1] <- c/(1-phi)
  
  
  for(i in 2:npnts)
  {
    xs[i] <- c + phi*xs[i-1]+rnorm(n=1,mean=0,sd=sigma_eps)
  }
  plot(xs)
  
  
  ## compute statistics:
  mu_theor <- c/(1.0-phi)
  var_theor <- (sigma_eps^2)/(1.0-phi^2)
  tau_theor <- -1.0/log(phi)
  print("theoretical mean:")
  print(mu_theor)
  print("theoretical variance: ")
  print(var_theor)
  print("theoretical lifetime: ")
  print(tau_theor)
  
  var_exp <- sd(xs)^2
  mean_exp <- mean(xs)
  print("experimental mean: ")
  print(mean_exp)
  print("experimental variance: ")
  print(var_exp)
  
  npnts_autocorr <- 50
  acf_xs <- array(0,dim=c(npnts_autocorr))
  for(i in 1:npnts_autocorr)
  {
    acf_xs[i] <- phi^{i-1}
  }
  plot(acf_xs)
  return(xs)
}

## obtain the parameters c,phi and sigma_eps for an AR(1) - process
Obtain_Parameters_For_AR1_Process <- function(mean_value,variance,lifetime)
{
  phi <- exp(-1.0/lifetime)
  c <- (1-phi)*(mean_value)
  sigma_eps <- sqrt((1-phi^2)*variance)
  
  print("phi: ")
  print(phi)
  print("c: ")
  print(c)
  print("sigma_eps:")
  print(sigma_eps)
}