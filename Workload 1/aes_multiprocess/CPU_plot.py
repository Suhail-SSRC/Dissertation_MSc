def scatter_plot(): # Dissertation AES plots
   # Read the CSV file
    df = pd.read_csv('M3_cpu4.csv', names=['PID', 'USER', 'PR', 'NI', 
'VIRT', 'RES', 'SHR', 'S', '%CPU', '%MEM', 'TIME+', 'COMMAND'])
    y1 = df['%CPU'].values.reshape(len(df['%CPU'].values), 1)
    x1 = np.arange(len(y1)).reshape(len(y1), 1)
    Y = np.vstack((y1))
    X = np.vstack((x1))

    # Calculate the time in seconds based on the number of entries
    total_entries = len(df)
    time_in_minutes = np.arange(total_entries) / 60.0

    # Compute CPU consumption over 10-minute periods
    interval_points = np.arange(0, np.ceil(time_in_minutes[-1]), 10)
    cpu_consumption_intervals = []

    for interval in interval_points:
        start_index = int(interval * 6)
        end_index = int((interval + 10) * 6)
        interval_cpu_consumption = np.mean(Y[start_index:end_index])
        cpu_consumption_intervals.append(interval_cpu_consumption)

    # Calculate the maximum CPU consumption
    max_cpu_index = np.argmax(Y)
    max_cpu_value = float(Y[max_cpu_index])

    # Create scatter plot with connecting lines
    plt.plot(interval_points, cpu_consumption_intervals, marker='o', 
linestyle='-')
    plt.scatter(interval_points[max_cpu_index // 600], max_cpu_value, 
color='red', label=f'Max CPU: {max_cpu_value:.2f}%')

    # Set labels and title
    plt.xlabel('Time (minutes)')
    plt.ylabel('CPU Consumption (%)')
    plt.title('CPU 4 Consumption of AES Encryption CTR mode\n with Key 
Length 256 bits (10 minutes interval) Multiprocess', fontsize=12)

    # Create legend
    plt.legend()

    # Save and show the plot
    plt.savefig("CPU_Consumptions_AESENC256_multiprocess_4.pdf", 
format="pdf")
    plt.show()
