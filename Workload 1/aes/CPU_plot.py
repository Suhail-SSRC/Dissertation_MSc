def scatter_plot(): # Dissertation AES plots
    # Read the CSV file
    df = pd.read_csv('M1.csv', names=['PID', 'USER', 'PR', 'NI', 'VIRT', 'RES', 'SHR', 'S', '%CPU', '%MEM', 'TIME+', 'COMMAND'])
    y1 = df['%CPU'].values.reshape(len(df['%CPU'].values),1)
    x1 = np.arange(len(y1)).reshape(len(y1),1)
    Y = np.vstack((y1))
    X = np.vstack((x1))
    indx = np.argmax(Y)
    index_min = np.argmin(Y)
    label_str = " Max CPU = " + str(Y[indx])
    
    # Calculate the time in seconds based on the number of entries
    total_entries = len(df)
    time_in_seconds = np.arange(total_entries)
    time_in_minutes = time_in_seconds / 60.0

    # Compute CPU consumption over 10-minute periods
    cpu_consumption = df.groupby(np.floor(time_in_minutes / 10))['%CPU'].mean()

    # Create scatter plot with connecting lines
    plt.plot(cpu_consumption.index * 10, cpu_consumption.values, marker='o', linestyle='-')
    plt.scatter(X[indx],Y[indx],label = label_str,s = 50,color = 'red')
    
    # m = plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
    #     ncol=2, mode="expand", borderaxespad=2.,fontsize=8)
    plt.legend(loc='best',prop={'size': 10})

    # Set labels and title
    plt.xlabel('Time (minutes)')
    plt.ylabel('CPU Consumption (%)')
    plt.title('CPU Consumption of AES Encryption CTR mode\n with Key Length 256 bits(10 minutes interval)',fontsize=12)

    plt.savefig("CPU_Consumptions_AESENC256.pdf",format = "pdf")

    # Show the plot
    plt.show()
