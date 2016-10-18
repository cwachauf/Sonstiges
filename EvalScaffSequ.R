EvaluateScaffoldSequence <- function()
{
  require("stringr")
  sequ <- scan(file="7560_sequenz.txt",what="character")
  print(sequ)
  str_locs <- str_locate_all(sequ,"ACTG")
  print(str_locs)
  ## do some tests:
  ## count the tupels of length
  vec_int_sequ <- CreateTupelIntegerSequences(7)
  list_str_sequ <- ConvertTupelSequence(vec_int_sequ)
  print(vec_int_sequ)
  
  num_rows <- length(list_str_sequ)
  print(num_rows)
  
  frequencies <- array(0,dim=c(num_rows))
  
  for(i in 1:num_rows)
  {
    test <- str_locate_all(sequ,list_str_sequ[i])
    print(test)
    print(lengths(test)/2)
    frequencies[i] <- lengths(test)/2
    #frequencies[i] <- nrow(test)
    # if(!is.null(test))
   # {
   #   frequencies[i] <- nrow(test)
   # }
      ##print(test)
  }
  hist(frequencies)
  ## count for all tupels the number of occurences..:
  
  
}

CreateTupelIntegerSequences <- function(n_order)
{
  num_tupels <- 4^(n_order)
  print(num_tupels)
  
  curr_vector <- array(0,dim=c(n_order))
  curr_vector <- array(0,dim=c(num_tupels,n_order))
  
  for(i in 1:(num_tupels-1))
  {
    for(j in 1:(n_order))
    {
      factor <- 4^(n_order-j)
      term1 <- floor(i/factor)
      curr_vector[i+1,j] <- term1 %% 4
    }
  }
  return(curr_vector)
}

ConvertTupelSequence <- function(integer_sequ_vector)
{
  num_rows <- nrow(integer_sequ_vector)
  num_columns <- ncol(integer_sequ_vector) 
  list_of_str <- ""
  for(ind_row in 1:num_rows)
  {  
    curr_str <- ""
    for(ind_col in 1:num_columns)
    {
      
      curr_int <- integer_sequ_vector[ind_row,ind_col]
      if(curr_int==0)
      {
        curr_str <- paste0(curr_str,"A")
      }
      else if(curr_int==1)
      {
        curr_str <- paste0(curr_str,"C")
      }
      else if(curr_int==2)
      {
        curr_str <- paste0(curr_str,"G")
      }
      else if(curr_int==3)
      {
        curr_str <- paste0(curr_str,"T")
      }
      
    }
   ## print(curr_str)
    if(ind_row==1)
    {
      list_of_str <- curr_str
    }
    else
    {
      list_of_str <- c(list_of_str,curr_str)
    }
  }
  ## Return a list of strings:
  return(list_of_str)
}



