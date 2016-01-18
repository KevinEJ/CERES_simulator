import os

os.chdir("./Result") # change work dir

file_golden = open("error_free_result.txt", 'r')
file_final = open("final_result.txt", 'r')
#[task_num,times] = Func.countTimes(file_golden, file_final)

line_list = file_golden.readlines()
line_num=len(line_list)
print "Free lines: %d" %(len(line_list))

error_list = file_final.readlines()
error_num=len(error_list)

exec_num=error_num/line_num
print "Total Exec. Times: %d" %(exec_num)

x=y=0
nowline=0
errorsum=0
errortemp=0
isError=False
resultcount=0
total_count = 0 

while (y < (exec_num)):
    #print "\nExec %d " %(y)
    while (x < (line_num)):
        nowline=y*line_num+x
        print "now line = " , nowline 
        #print "now line_num = " , line_num 
        #print "line list x = " , line_list[x] 
        #print "line list x.size  " , len(line_list[x])
        if len(line_list[x])==9:
            print "line list x  " , line_list[x]
            total_count = total_count + 1
        if ((line_list[x] != error_list[nowline]) and (x!=0)):
            #print "    line %d" %(y*line_num+x)
            isError=True
            a=list(error_list[nowline].split(' '))
            b=list(line_list[x].split(' '))
            #print "a = " , a , " len " , len(a)  
            #print "b = " , b
            if a[0]=='Count':
                x = x + 1
                continue
            #print "a[8] = " , a[8]
            resultcount=resultcount+1 
            z=9  ## Starts with nine             
            '''
            while (z<int(len(a))-1): ##Last is endline
                try:
                    gg=float(a[z])
                except ValueError:
                    print "FUCK "+a[z]
                errortemp=errortemp+float(a[z])-float(b[z])                
                print "z - " , z 
                print "a[z] = " , a[z]
                if float(a[z])!=float(b[z]):
                    print"      answer %d flip" %(z-9)
                    resultcount=resultcount+1 
                z=z+1
            print " x  = " , x , "line_num = " , line_num 
            
            
            if (x==line_num-1):
                z=9
                while (z<int(len(a))-1): ##Last is endline
                    try:
                        gg=float(a[z])
                    except ValueError:
                        print "FUCK "+a[z]
                    if (float(a[z])!=float(b[z])):
                        print"      answer %d flip" %(z-9)
                        resultcount=resultcount+1                
                    z=z+1
            '''
        x=x+1
    x=0
    if (isError):
        print "    Error in this exec %f \n" %(errortemp)
    isError=False
    errorsum=errorsum+errortemp
    errortemp=0
    y=y+1

# total core used 
print "last line = " , line_list[len(line_list)-1] 
last_line=list(line_list[len(line_list)-1].split(' '))
print "last line = " , last_line[2]  


print "Total Error is %f" %(errorsum)
print "Total Result fail is %d" %(resultcount)

file_anal = open("accu.txt",'a')
file_anal.write('Total Result fail is '+str(resultcount)+'/'+str(total_count)+'\n')
fuck="%.3f" %(100*float(resultcount)/(total_count))
file_anal.write('Error Rate is '+fuck+'%\n')
file_anal.write('total_core_used ' + last_line[2] + '\n')   
   
file_golden.close()
file_final.close()


#file_golden = open("error_free_result.txt", 'r')
#file_analysis = open("final_result.txt", 'r')

#Func.CeresStatistic(task_num, times, file_golden, file_analysis)

#file_golden.close()
#file_final.close()
