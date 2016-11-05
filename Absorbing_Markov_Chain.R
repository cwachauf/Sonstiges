## playing around with Absorbing Markov Chains...

Test_Absorbing_MCs <- function()
{
  require(Matrix)
  ## as an example: look at the following case:
  ## 1 <---> 2 --> 3, i.e. "3" is an absorbing state
  ## and 1 and 2 are transient states..
  ## 1 ---> 2 with rate lambda1, 2---> 1 with rate lambda 2
  ## and finally the absorption rate from 2 to 3  2 ---> 3 with lambda3
  
  
  n_states <- 3
  
  ## values of the rates:
  lambda1 <- 0.5
  lambda2 <- 0.5
  lambda3 <- 0.8
  
  ## set up the generator matrix:
  ##
  Q <- array(0,dim=c(n_states,n_states))
  Q[1,2] <- lambda1
  Q[1,1] <- -lambda1
  Q[2,1] <- lambda2
  Q[2,3] <- lambda3
  Q[2,2] <- -(lambda2+lambda3)
  D0 <- Q[1:(n_states-1),1:(n_states-1)]
  ENS <- solve(-D0)
  print(Q)
  print(D0)
  print(ENS)
  
  ntimes <- 100
  xs <- seq(from=0,to=20,length=ntimes)
  
  Fs <- array(0,dim=c(ntimes))
  pis <- cbind(1,0)
  one <- rbind(1,1)
  print(one)
  for(i in 1:ntimes)
  {
    Temp <- D0*xs[i] 
    mat_exp <- expm(Temp)
    res <- pis%*%mat_exp%*%one
    ##print(pis)
    
  ##  print(res)
    Fs[i] <- 1.0 - res[1,1]
  }
  plot(xs,Fs,type="l")
}