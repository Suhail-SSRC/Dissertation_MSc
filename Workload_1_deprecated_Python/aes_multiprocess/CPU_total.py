def scatter_plot(): # Dissertation AES plots
    # Read the CSV file
    df = pd.read_csv('M3_total.csv', names=['PID', 'USER', 'PR', 'NI', 'VIRT', 'RES', 'SHR', 'S', 
'%CPU', '%MEM', 'TIME+', 'COMMAND'])
    y1 = df['%CPU'].values.reshape(len(df['%CPU'].values),1)
    x1 = np.arange(len(y1)).reshape(len(y1),1)
    Y = np.vstack((y1))
    X = np.vstack((x1))
    
    # Calculate the time in seconds based on the number of entries
    total_entries = len(df)
    time_in_seconds = np.arange(total_entries)
    time_in_minutes = time_in_seconds / 60.0

    # Compute CPU consumption over 10-minute periods
    cpu_consumption = df.groupby(np.floor(time_in_minutes / 10))['%CPU'].mean()

    # Create scatter plot with connecting lines
    plt.plot(cpu_consumption.index * 10, cpu_consumption.values, marker='o', linestyle='-')
    
    # plt.legend(loc='best', prop={'size': 10})

    # Set labels and title
    plt.xlabel('Time (minutes)')
    plt.ylabel('CPU Consumption (%)')
    plt.title('CPU Consumption of AES Encryption CTR mode\n with Key Length 256 bits(10 minutes 
interval) Multiprocess',fontsize=12)

    plt.savefig("CPU_Consumptions_AESENC256_multiprocess.pdf",format = "pdf")

    # Show the plot
    plt.show()
