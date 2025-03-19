import math

import numpy
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from scipy.stats import shapiro

N = 50_000
MIN_ARRIVAL_INTERVAL = 2
MAX_ARRIVAL_INTERVAL = 10
AVG_ARRIVAL_DELAY = 4

MIN_REFUELING_TIME = 15
MAX_REFUELING_TIME = 30
MEAN = 25
STANDARD_DEVIATION = 5

REFUELERS_COUNT = 5

MAX_CIRCLES_COUNT = 2
CIRCLE_DURATION = 5

ITERATIONS_COUNT = 1000
DEFAULT_ITERATION_TIME = 360

CIRCLES_METRIC_NAME = "circles"
OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME = "occupied_refuelers"
PLANES_LEAVED_METRIC_NAME = "planes_leaved"
TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME = "time"

#Generate arrival times with exponential distribution
class ArrivalTimesGenerator:
    def __init__(self, n, a, b, avg_delay):
        lambda_param = avg_delay
        exp_distribution = np.random.exponential(1/lambda_param, n)
        plane_delays= np.round(a + exp_distribution * (b - a))
        self.plane_arrivals = np.cumsum(plane_delays)
        self.counter = -1

    def next(self):
        self.counter += 1
        return self.plane_arrivals[self.counter]

#Generate refueling times with normal distribution
class RefuelingTimesGenerator:
    def __init__(self, n, a, b, mean, standard_deviation):
        self.refueling_times = np.round(np.clip(np.random.normal(mean, standard_deviation, n), a, b))
        self.counter = -1

    def next(self):
        self.counter += 1
        return self.refueling_times[self.counter]

class Plane:
    def __init__(self, arrival_time, refueling_time, index, circles_amount = 0):
        self.arrival_time = arrival_time
        self.refueling_time = refueling_time
        self.circles_amount = circles_amount
        self.index = index

    def inc_circle_if_required(self, t):
        if (t - self.arrival_time) % CIRCLE_DURATION == 0:
            self.circles_amount += 1

#Generate plane with arrival time and refueling time
class PlaneGenerator:
    def __init__(self, arrival_times_generator, refueling_times_generator):
        self.arrival_times_generator = arrival_times_generator
        self.refueling_times_generator = refueling_times_generator
        self.planes = []
        self.counter = 0
        for i in range(len(arrival_times_generator.plane_arrivals)):
            self.planes.append(Plane(arrival_times_generator.next(), refueling_times_generator.next(), i))

    def peek(self):
        return self.planes[self.counter]

    def pop(self):
        self.counter += 1
        return self.planes[self.counter - 1]

class Refueler:
    def __init__(self, free_at = 0, is_free = True):
        self.free_at = free_at
        self.is_free = is_free

class RefuelerPool:
    def __init__(self, n):
        self.refuelers = []
        for i in range(n):
            self.refuelers.append(Refueler())

    def has_free_refueler(self):
        for i in range(len(self.refuelers)):
            if self.refuelers[i].is_free:
                return True
        return False

    def get_free_refueler(self):
        for i in range(len(self.refuelers)):
            if self.refuelers[i].is_free:
                return self.refuelers[i]
        return None

    def get_occupied_refuelers_amount(self):
        counter = 0
        for i in range(len(self.refuelers)):
            if not self.refuelers[i].is_free:
                counter += 1
        return counter

    def free_refuelers(self, t):
        for i in range(len(self.refuelers)):
            refueler = self.refuelers[i]
            if (refueler.free_at <= t) and (refueler.is_free == False):
                refueler.is_free = True
                refueler.free_at = 0
                optional_print("Refueler %d set free" % i)
            if refueler.is_free:
                optional_print("Refueler %d free" % i)
            else:
                optional_print("Refueler %d occupied" % i)

class WaitingPlaneQueue:
    def __init__(self):
        self.waiting_planes = []

    def add(self, plane):
        self.waiting_planes.append(plane)

    def pop(self):
        return self.waiting_planes.pop(0)

    def remove_exhausted(self):
        removed_planes = []
        i = 0
        while i < len(self.waiting_planes):
            if self.waiting_planes[i].circles_amount >= MAX_CIRCLES_COUNT:
                removed_planes.append(self.waiting_planes[i])
                self.waiting_planes.pop(i)
            else:
                i += 1
        for i in range(len(removed_planes)):
            optional_print("Plane flies to spare airport, plane(arr: %d, ref: %d)" % (removed_planes[i].arrival_time, removed_planes[i].refueling_time))
        return removed_planes

    def inc_planes_circle_if_required(self, t):
        for i in range(len(self.waiting_planes)):

            self.waiting_planes[i].inc_circle_if_required(t)

class NumericMetricsCollector:
    def __init__(self):
        self.metrics = {}

    def init_metric_if_not_present(self, metric_name, value):
        if metric_name not in self.metrics.keys():
            self.metrics[metric_name] = value

    def push_to_metric(self, metric_name, value):
        self.init_metric_if_not_present(metric_name, [])
        self.metrics[metric_name].append(value)

    def add_to_metric(self, metric_name, value):
        self.init_metric_if_not_present(metric_name, 0)
        self.metrics[metric_name] += value

    def get_avg_metric(self, metric_name):
        if not metric_name in self.metrics:
            return 0
        if len(self.metrics[metric_name]) == 0:
            return 0
        value = numpy.average(self.metrics[metric_name])
        return value

    def get_metric(self, metric_name):
        if not metric_name in self.metrics:
            return 0
        return self.metrics[metric_name]

class NumericMetricsVerifier:
    def is_normal_distribution_ks(self, data, alpha):
        mean = np.mean(data)
        standard_deviation = np.std(data)

        #It means all values are 0
        if mean == 0 and standard_deviation == 0:
            return False

        d, p_value = stats.kstest(data, 'norm', args=(mean, standard_deviation))
        if p_value < alpha:
            return False
        return True

    def is_normal_distribution_shapiro(self, data, alpha):
        #It means all values are 0
        if not any(data):
            return False

        stat, p = shapiro(data)
        if p <= alpha:
            return False
        return True

    #Standart deviation as point evaluation
    def point_evaluation(self, data):
        return np.std(data)

    #(1 - alpha) - percent of values that have to fit our interval
    def interval_evaluation(self, data, alpha):
        if alpha == 0:
            return np.min(data), np.max(data)
        mean = np.mean(data)
        standard_deviation = np.std(data)
        n = len(data)
        t_critical = stats.t.ppf(1 - alpha / 2, df=n-1) #Critical value of t-criteria
        standard_error = standard_deviation / np.sqrt(n)
        return mean - t_critical * standard_error, mean + t_critical * standard_error

    def calculate_se(self, iterations_count_array):
        iterations_count_array.sort()
        max_iterations_count = np.max(iterations_count_array)
        metrics_collector, last_value_metric_collector = start_model(max_iterations_count)
        se_map = {
            CIRCLES_METRIC_NAME: [],
            PLANES_LEAVED_METRIC_NAME: [],
            OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME: [],
            TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME: []
        }
        for i in range(0, len(iterations_count_array)):
            iterations_count = iterations_count_array[i]

            circles_metric_data = metrics_collector.get_metric(CIRCLES_METRIC_NAME)[0:iterations_count]
            circles_metric_data_deviation = np.std(circles_metric_data)
            se_map[CIRCLES_METRIC_NAME].append(math.sqrt(circles_metric_data_deviation / iterations_count))

            planes_leaved_metric_data = metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME)[0:iterations_count]
            planes_leaved_metric_data_deviation = np.std(planes_leaved_metric_data)
            se_map[PLANES_LEAVED_METRIC_NAME].append(math.sqrt(planes_leaved_metric_data_deviation / iterations_count))

            occupied_refuelers_on_plane_arrival_metric_data = metrics_collector.get_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME)[0:iterations_count]
            occupied_refuelers_on_plane_arrival_metric_data_deviation = np.std(occupied_refuelers_on_plane_arrival_metric_data)
            se_map[OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME].append(math.sqrt(occupied_refuelers_on_plane_arrival_metric_data_deviation / iterations_count))

            time_from_arrival_to_exit_metric_data = metrics_collector.get_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME)[0:iterations_count]
            time_from_arrival_to_exit_metric_data_deviation = np.std(time_from_arrival_to_exit_metric_data)
            se_map[TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME].append(math.sqrt(time_from_arrival_to_exit_metric_data_deviation / iterations_count))
        return se_map

    def print_se(self, se_map):
        metric_names = se_map.keys()
        for metric_name in metric_names:
            print(f"{metric_name}: {se_map[metric_name]}")

    def calculate_stabilization_ticks(self, metrics_collector, window_size, alpha, step = 1):
        stabilization_ticks = {
            CIRCLES_METRIC_NAME: math.inf,
            PLANES_LEAVED_METRIC_NAME: math.inf,
            OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME: math.inf,
            TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME: math.inf
        }
        for metric_name in metrics_collector.metrics.keys():
            for i in range(0, len(metrics_collector.get_metric(metric_name)) - window_size, step):
                data = metrics_collector.get_metric(metric_name)
                current_window = data[i:i + window_size]
                next_window = data[i + 1:i + 1 + window_size]
                cov = np.cov(current_window, next_window)[0, 1]
                max_zeros_percent_in_window = 0.7
                if abs(cov) < alpha and current_window.count(0) < window_size * max_zeros_percent_in_window and next_window.count(0) < window_size * max_zeros_percent_in_window:
                    stabilization_ticks[metric_name] = i
                    break
        return stabilization_ticks

    def verify_with_t_statistics(self, data1, data2, eps):
        n = len(data1)
        m = len(data2)
        dispersion1 = np.std(data1) ** 2 * n / (n - 1)
        dispersion2 = np.std(data2) ** 2 * m / (m - 1)
        E = abs(np.mean(data1) - np.mean(data2))
        Se = (n * dispersion1 + m * dispersion2) / (n + m - 2)
        t_crit = stats.t.ppf(eps, n + m - 2)
        t = E * math.sqrt(n * m / (Se * (n + m)))
        if t <= t_crit:
            return True
        return False

class PlotPainter:
    def draw_data_plot(self, data):
        plt.hist(data)
        plt.show()

    def draw_probability_density_plot(self, data):
        plt.hist(x=data, density=True)
        plt.show()

    def draw_point_plot(self, x_axis, y_axis, x_lim = None, y_lim = None):
        #Calculate trend line formula
        slope, intercept, r_value, p_value, std_err = stats.linregress(x_axis, y_axis)
        y_trend = slope * np.array(x_axis) + intercept

        plt.figure(figsize=(8, 4))
        if x_lim is not None and y_lim is not None:
            plt.xlim(x_lim)
            plt.ylim(y_lim)
        plt.scatter(x_axis, y_axis)
        plt.plot(x_axis, y_trend, label='Линия тренда', color='red')
        plt.xlabel(f"y = {slope}x + {intercept}")
        plt.show()

    def draw_data_with_borders(self, data, low_border, high_border):
        plt.figure()
        plt.axhline(y = low_border, color = 'r', linestyle = '-')
        plt.axhline(y = high_border, color = 'b', linestyle = '-')
        x = range(1, len(data) + 1)
        plt.scatter(x, data)
        plt.show()

    def draw_complex_point_plot(self, x_axis, y_axis1, y_axis2):
        plt.figure()
        plt.scatter(x_axis, y_axis1, color='blue', label='y1')
        plt.scatter(x_axis, y_axis2, color='red', label='y2')
        plt.show()

    def draw_complex_point_plot_v2(self, x_axis1, y_axis1, x_axis2, y_axis2):
        plt.figure()
        plt.scatter(x_axis1, y_axis1, color='blue', label='y1')
        plt.scatter(x_axis2, y_axis2, color='red', label='y2')
        plt.show()

    def draw_point_plot_with_step(self, x_axis, y_axis, step):
        y_axis_step = y_axis[0:len(y_axis):(step - 1)]
        x_axis_step = x_axis[0:len(x_axis):(step - 1)]
        plt.figure()
        plt.scatter(x_axis_step, y_axis_step)
        if len(x_axis) != 0 and len(y_axis) != 0:
            plt.xlim([0, np.max(x_axis_step) * 1.1])
            plt.ylim([0, np.max(y_axis_step) * 1.1])
        plt.show()

def start_iteration(iteration_time = DEFAULT_ITERATION_TIME, arrival_times_generator = None):
    if arrival_times_generator is None:
        arrival_times_generator = ArrivalTimesGenerator(N, MIN_ARRIVAL_INTERVAL,
                                                        MAX_ARRIVAL_INTERVAL, AVG_ARRIVAL_DELAY)
    refueling_times_generator = RefuelingTimesGenerator(N, MIN_REFUELING_TIME,
                                                        MAX_REFUELING_TIME, MEAN, STANDARD_DEVIATION)
    plane_generator = PlaneGenerator(arrival_times_generator, refueling_times_generator)
    refueler_pool = RefuelerPool(REFUELERS_COUNT)
    waiting_plane_queue = WaitingPlaneQueue()
    local_metrics_collector = NumericMetricsCollector()
    time_metrics_collector = NumericMetricsCollector()
    local_metrics_collector.init_metric_if_not_present(CIRCLES_METRIC_NAME, [])
    for t in range(iteration_time + 1):
        optional_print("Current tick: %d" % t)
        waiting_plane_queue.inc_planes_circle_if_required(t)

        refueler_pool.free_refuelers(t)

        while refueler_pool.has_free_refueler() and len(waiting_plane_queue.waiting_planes) > 0:
            refueler = refueler_pool.get_free_refueler()
            refueler.is_free = False
            waiting_plane = waiting_plane_queue.pop()
            #Circles metric
            local_metrics_collector.push_to_metric(CIRCLES_METRIC_NAME, waiting_plane.circles_amount)
            refueler.free_at = t + waiting_plane.refueling_time
            #Time metric
            local_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, refueler.free_at - waiting_plane.arrival_time)
            optional_print("Plane(arr: %d, ref: %d) with index %d placed refueler"
                           % (waiting_plane.arrival_time, waiting_plane.refueling_time,  waiting_plane.index))

        exhausted_planes = waiting_plane_queue.remove_exhausted()
        exhausted_planes_count = len(exhausted_planes)
        #Time metric
        for i in range(exhausted_planes_count):
            local_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, t - exhausted_planes[i].arrival_time)

        #Spare airport metric
        local_metrics_collector.add_to_metric(PLANES_LEAVED_METRIC_NAME, exhausted_planes_count)
        #Circles metric
        for i in range(exhausted_planes_count):
            local_metrics_collector.push_to_metric(CIRCLES_METRIC_NAME, MAX_CIRCLES_COUNT)

        nextPlane = plane_generator.peek()

        if nextPlane.arrival_time == t:
            local_metrics_collector.push_to_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME, refueler_pool.get_occupied_refuelers_amount())
            arrived_plane = plane_generator.pop()
            optional_print("Plane(arr: %d, ref: %d) with index %d arrived"
                           % (arrived_plane.arrival_time, arrived_plane.refueling_time, arrived_plane.index))
            if refueler_pool.has_free_refueler():
                refueler = refueler_pool.get_free_refueler()
                refueler.is_free = False
                refueler.free_at = arrived_plane.arrival_time + arrived_plane.refueling_time
                #Time metric
                local_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, refueler.free_at - arrived_plane.arrival_time)

                optional_print("Plane(arr: %d, ref: %d) with index %d placed refueler"
                               % (arrived_plane.arrival_time, arrived_plane.refueling_time,  arrived_plane.index))
            else:
                waiting_plane_queue.add(arrived_plane)
                optional_print("Plane(arr: %d, ref: %d) with index %d placed in queue"
                               % (arrived_plane.arrival_time, arrived_plane.refueling_time,  arrived_plane.index))

        time_metrics_collector.push_to_metric(CIRCLES_METRIC_NAME, local_metrics_collector.get_avg_metric(CIRCLES_METRIC_NAME))
        time_metrics_collector.push_to_metric(PLANES_LEAVED_METRIC_NAME, local_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME))
        time_metrics_collector.push_to_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME, local_metrics_collector.get_avg_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME))
        time_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, local_metrics_collector.get_avg_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME))
        optional_print("\n\n")
    return local_metrics_collector, time_metrics_collector

def start_model(iterations_count, iteration_time = DEFAULT_ITERATION_TIME):
    global_metrics_collector = NumericMetricsCollector()
    global_last_metric_value_collector = NumericMetricsCollector()
    for i in range(iterations_count):
        local_metrics_collector, time_metrics_collector = start_iteration(iteration_time)
        global_metrics_collector.push_to_metric(CIRCLES_METRIC_NAME, local_metrics_collector.get_avg_metric(CIRCLES_METRIC_NAME))
        global_metrics_collector.push_to_metric(PLANES_LEAVED_METRIC_NAME, local_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME))
        global_metrics_collector.push_to_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME, local_metrics_collector.get_avg_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME))
        global_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, local_metrics_collector.get_avg_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME))

        global_last_metric_value_collector.push_to_metric(CIRCLES_METRIC_NAME, time_metrics_collector.get_metric(CIRCLES_METRIC_NAME)[len(time_metrics_collector.get_metric(CIRCLES_METRIC_NAME)) - 1])
        global_last_metric_value_collector.push_to_metric(PLANES_LEAVED_METRIC_NAME, time_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME)[len(time_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME)) - 1])
        global_last_metric_value_collector.push_to_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME, time_metrics_collector.get_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME)[len(time_metrics_collector.get_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME)) - 1])
        global_last_metric_value_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, time_metrics_collector.get_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME)[len(time_metrics_collector.get_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME)) - 1])
    return global_metrics_collector, global_last_metric_value_collector

PRINT = False
def optional_print(message):
    if PRINT:
        print(message)

numeric_metrics_verifier = NumericMetricsVerifier()
plot_painter = PlotPainter()

# Task 1
# Normal distribution verification can be done either by ks or shapiro method
#task1_metrics_collector, task1_time_metrics_collector = start_model(300)
# print("Is circles amount has normal distribution? %s" % numeric_metrics_verifier.is_normal_distribution_shapiro(task1_metrics_collector.get_metric(CIRCLES_METRIC_NAME), 0.05))
# print("Is landed at spare airport planes amount has normal distribution? %s" % numeric_metrics_verifier.is_normal_distribution_shapiro(task1_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME), 0.05))
# print("Is occupied refuelers on plane arrival amount has normal distribution? %s" % numeric_metrics_verifier.is_normal_distribution_shapiro(task1_metrics_collector.get_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME), 0.05))
#print("Is time before leaving the system has normal distribution? %s" % numeric_metrics_verifier.is_normal_distribution_shapiro(task1_metrics_collector.get_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME), 0.05))

# Draw plots
# plot_painter.draw_probability_density_plot(task1_metrics_collector.get_metric(CIRCLES_METRIC_NAME))
# plot_painter.draw_probability_density_plot(task1_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME))
# plot_painter.draw_probability_density_plot(task1_metrics_collector.get_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME))
#plot_painter.draw_probability_density_plot(task1_metrics_collector.get_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME))

# Task2
# print("\n")
# task2_metrics_collector, task2_time_metrics_collector = start_model(10)
# metric_name = TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME
# # Evaluations
# alpha = 0.01
# point_evaluation = numeric_metrics_verifier.point_evaluation(task2_metrics_collector.get_metric(metric_name))
# print(f"Point evaluation(standard deviation) for {metric_name}: {point_evaluation:.2f}")
# low_border, high_border = numeric_metrics_verifier.interval_evaluation(task2_metrics_collector.get_metric(metric_name), alpha)
# print(f"Interval for {metric_name}: ({low_border:.2f}; {high_border:.2f})")
# plot_painter.draw_data_with_borders(task2_metrics_collector.get_metric(metric_name), low_border, high_border)

# Task3
# print("\n")
# metric_name = TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME
# iterations_count_array = [10, 40, 50, 200]
# se_map = numeric_metrics_verifier.calculate_se(iterations_count_array)
# numeric_metrics_verifier.print_se(se_map)
# plot_painter.draw_point_plot(iterations_count_array, se_map[metric_name])
#
# alpha = 0.05
# se_value = 0.1
# i = 10
# while True:
#     print(f"Start iteration: {i}")
#     iterations_count = [i]
#     se_map = numeric_metrics_verifier.calculate_se(iterations_count)
#     value = se_map[metric_name][0]
#     deviation = alpha * value
#     if value - deviation <= se_value <= value + deviation:
#         print(f"Iterations count: {i}, se: {value}")
#         break
#     if value <= se_value:
#         i -= 1
#     else:
#         i += 10


# Task4
# metric_name = OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME
#
# data = {}
# for i in range(AVG_ARRIVAL_DELAY - 2, AVG_ARRIVAL_DELAY + 2 + 1):
#     arrival_times_generator = ArrivalTimesGenerator(N, MIN_ARRIVAL_INTERVAL,
#                                                     MAX_ARRIVAL_INTERVAL, i)
#     local_metrics_collector_task4, time_metrics_collector_task4 = start_iteration(360, arrival_times_generator)
#     data[i] = local_metrics_collector_task4.get_avg_metric(metric_name)
# x_axis = list(data.keys())
# y_axis = list(data.values())
# plot_painter.draw_point_plot(x_axis, y_axis, np.max(x_axis) + 2, np.max(y_axis) + 5)

# TODO: deprecated
# local_metrics_collector_task4, time_metrics_collector_task4 = start_iteration(360, arrival_times_generator)
# print(time_metrics_collector_task4.get_metric(metric_name))
# metric_data_task4 = time_metrics_collector_task4.get_metric(metric_name)
# ticks_task4 = range(0, len(metric_data_task4))
# plot_painter.draw_point_plot(ticks_task4, metric_data_task4)
#
# arrival_times_generator.plane_arrivals += 1
# arrival_times_generator.counter = -1
# local_metrics_collector_task4_1, time_metrics_collector_task4_1 = start_iteration(360, arrival_times_generator)
# print(time_metrics_collector_task4_1.get_metric(metric_name))
# metric_data_task4 = time_metrics_collector_task4_1.get_metric(metric_name)
# ticks_task4 = range(0, len(metric_data_task4))
# plot_painter.draw_point_plot(ticks_task4, metric_data_task4)
#
# arrival_times_generator.plane_arrivals -= 2
# arrival_times_generator.counter = -1
# local_metrics_collector_task4_2, time_metrics_collector_task4_2 = start_iteration(360, arrival_times_generator)
# print(time_metrics_collector_task4_2.get_metric(metric_name))
# metric_data_task4 = time_metrics_collector_task4_2.get_metric(metric_name)
# ticks_task4 = range(0, len(metric_data_task4))
# plot_painter.draw_point_plot(ticks_task4, metric_data_task4)


# Task 5
# step = 20
# window_size = 20
# ticks_count = 1000
# iterations_count = 10
# metric_name_task5 = CIRCLES_METRIC_NAME
# local_metrics_collector_task5, time_metrics_collector_task5 = start_iteration(ticks_count)
# metric_data_task5 = time_metrics_collector_task5.get_metric(metric_name_task5)
# ticks_task5 = range(0, len(metric_data_task5))
# plot_painter.draw_point_plot_with_step(ticks_task5, metric_data_task5, step)
# stabilization_tick = int(input("Input stabilization tick: "))
# right_border_tick = int(input("Input right border tick: "))
#
# metrics_collector, last_value_metrics_collector = start_model(iterations_count, ticks_count)
# data = metrics_collector.get_metric(metric_name_task5)
#
# class ExitLoops(Exception):
#     pass
#
# data_stabilized = []
# try:
#     for i in range(right_border_tick, ticks_count + 1, (ticks_count - right_border_tick) // 10):
#         for j in range(iterations_count, iterations_count * 5 + 1, iterations_count):
#             data_stabilized = []
#             for k in range(j):
#                 metrics_collector, time_metrics_collector = start_iteration(i)
#                 avg_metric = np.mean(time_metrics_collector.get_metric(metric_name_task5)[stabilization_tick:])
#                 data_stabilized.append(avg_metric)
#             is_stabilized = numeric_metrics_verifier.verify_with_t_statistics(data, data_stabilized, 0.95)
#             print(f"Is stabilized on {j} iterations count and right border on {i} : {is_stabilized}")
#             if is_stabilized:
#                 plot_painter.draw_complex_point_plot_v2(range(1, iterations_count + 1), data, range(1, j + 1), data_stabilized)
#                 raise ExitLoops
# except ExitLoops:
#     print("")

# if stabilization_ticks[metric_name_task5] != math.inf:
#     plot_painter.draw_point_plot_with_step(ticks_task5[stabilization_ticks[metric_name_task5]:], metric_data_task5[stabilization_ticks[metric_name_task5]:], step)
#     print(f"Is model adequate: {numeric_metrics_verifier.verify_with_t_statistics(metric_data_task5, metric_data_task5[stabilization_ticks[metric_name_task5]:], 0.95)}")
# else:
#     plot_painter.draw_point_plot_with_step([], [], step)

# TODO: deprecated
# step = 20
# window_size = 20
# ticks_count = 1000
# metric_name_task5 = TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME
# local_metrics_collector_task5, time_metrics_collector_task5 = start_iteration(ticks_count)
# stabilization_ticks = numeric_metrics_verifier.calculate_stabilization_ticks(time_metrics_collector_task5, window_size, 0.0001, step)
# print(stabilization_ticks[metric_name_task5])
# metric_data_task5 = time_metrics_collector_task5.get_metric(metric_name_task5)
# ticks_task5 = range(0, len(metric_data_task5))
# plot_painter.draw_point_plot_with_step(ticks_task5, metric_data_task5, step)
# if stabilization_ticks[metric_name_task5] != math.inf:
#     plot_painter.draw_point_plot_with_step(ticks_task5[stabilization_ticks[metric_name_task5]:], metric_data_task5[stabilization_ticks[metric_name_task5]:], step)
#     print(f"Is model adequate: {numeric_metrics_verifier.verify_with_t_statistics(metric_data_task5, metric_data_task5[stabilization_ticks[metric_name_task5]:], 0.95)}")
# else:
#     plot_painter.draw_point_plot_with_step([], [], step)

# Task 6 (Can't be run with commented task 5)

# metrics_collector, time_metrics_collector = start_iteration(ticks_count)
#
# try:
#     for i in range(stabilization_tick, ticks_count, int(stabilization_tick * 1.5)):
#         data = []
#         for j in range(stabilization_tick, ticks_count, i):
#             data.append(np.mean(time_metrics_collector.get_metric(metric_name_task5)[j:(j + i)]))
#         is_stabilized = numeric_metrics_verifier.verify_with_t_statistics(data_stabilized, data, 0.95)
#         print(f"Is adequate with skip {right_border_tick} with interval size {i}: {is_stabilized}")
#         if is_stabilized:
#             plot_painter.draw_complex_point_plot_v2(range(1, len(data_stabilized) + 1), data_stabilized, range(1, len(data) + 1), data)
#             raise ExitLoops
# except ExitLoops:
#     print("")

# TODO: deprecated
# step = 200
# ticks_count = 10000
# metric_name = TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME
# small_iterations_collector, small_iterations_last_metric_value_collector = start_model(math.ceil(ticks_count / step), step)
# big_iteration_collector, big_time_iteration_collector = start_iteration(ticks_count)
#
# last_metric_values_in_small_iterations = small_iterations_last_metric_value_collector.get_metric(metric_name)
# step_metric_values_in_big_iteration = big_time_iteration_collector.get_metric(metric_name)[0:ticks_count:step]
# plot_painter.draw_complex_point_plot(range(0, ticks_count, step), last_metric_values_in_small_iterations, step_metric_values_in_big_iteration)
# print(f"Is model adequate: {numeric_metrics_verifier.verify_with_t_statistics(last_metric_values_in_small_iterations, step_metric_values_in_big_iteration, 0.95)}")
