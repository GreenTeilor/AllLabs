import math

import numpy
import numpy as np

N = 1000
MIN_ARRIVAL_INTERVAL = 2
MAX_ARRIVAL_INTERVAL = 10
AVG_ARRIVAL_DELAY = 4

MIN_REFUELING_TIME = 15
MAX_REFUELING_TIME = 30
MEAN = 25
STANDARD_DEVIATION = 5

REFUELERS_COUNT = 3

MAX_CIRCLES_COUNT = 2
CIRCLE_DURATION = 5

ITERATIONS_COUNT = 100
ITERATION_TIME = 120

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
                print("Refueler %d set free" % i)
            if refueler.is_free:
                print("Refueler %d free" % i)
            else:
                print("Refueler %d occupied" % i)

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
            print("Plane flies to spare airport, plane(arr: %d, ref: %d)" % (removed_planes[i].arrival_time, removed_planes[i].refueling_time))
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
        value = numpy.average(self.metrics[metric_name])
        if math.isnan(value):
            return 0
        return value

    def get_metric(self, metric_name):
        return self.metrics[metric_name]

global_metrics_collector = NumericMetricsCollector()
for i in range(ITERATIONS_COUNT):
    arrival_times_generator = ArrivalTimesGenerator(N, MIN_ARRIVAL_INTERVAL,
                                                    MAX_ARRIVAL_INTERVAL, AVG_ARRIVAL_DELAY)
    refueling_times_generator = RefuelingTimesGenerator(N, MIN_REFUELING_TIME,
                                                    MAX_REFUELING_TIME, MEAN, STANDARD_DEVIATION)
    plane_generator = PlaneGenerator(arrival_times_generator, refueling_times_generator)
    refueler_pool = RefuelerPool(REFUELERS_COUNT)
    waiting_plane_queue = WaitingPlaneQueue()
    local_metrics_collector = NumericMetricsCollector()
    local_metrics_collector.init_metric_if_not_present(CIRCLES_METRIC_NAME, [])
    for t in range(ITERATION_TIME + 1):
        print("Current tick: %d" % t)
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
            print("Plane(arr: %d, ref: %d) with index %d placed refueler"
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
            print("Plane(arr: %d, ref: %d) with index %d arrived"
                  % (arrived_plane.arrival_time, arrived_plane.refueling_time, arrived_plane.index))
            if refueler_pool.has_free_refueler():
                refueler = refueler_pool.get_free_refueler()
                refueler.is_free = False
                refueler.free_at = arrived_plane.arrival_time + arrived_plane.refueling_time
                #Time metric
                local_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, refueler.free_at - arrived_plane.arrival_time)

                print("Plane(arr: %d, ref: %d) with index %d placed refueler"
                      % (arrived_plane.arrival_time, arrived_plane.refueling_time,  arrived_plane.index))
            else:
                waiting_plane_queue.add(arrived_plane)
                print("Plane(arr: %d, ref: %d) with index %d placed in queue"
                      % (arrived_plane.arrival_time, arrived_plane.refueling_time,  arrived_plane.index))

        print("\n\n")
    global_metrics_collector.push_to_metric(CIRCLES_METRIC_NAME, local_metrics_collector.get_avg_metric(CIRCLES_METRIC_NAME))
    global_metrics_collector.push_to_metric(PLANES_LEAVED_METRIC_NAME, local_metrics_collector.get_metric(PLANES_LEAVED_METRIC_NAME))
    global_metrics_collector.push_to_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME, local_metrics_collector.get_avg_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME))
    global_metrics_collector.push_to_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME, local_metrics_collector.get_avg_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME))

print("Average circles amount: %f" % global_metrics_collector.get_avg_metric(CIRCLES_METRIC_NAME))
print("Average landed at spare airport: %f" % global_metrics_collector.get_avg_metric(PLANES_LEAVED_METRIC_NAME))
print("Average occupied refuelers on plane arrival: %f" % global_metrics_collector.get_avg_metric(OCCUPIED_REFUELERS_ON_PLANE_ARRIVAL_METRIC_NAME))
print("Average time before leaving the system: %f" % global_metrics_collector.get_avg_metric(TIME_FROM_ARRIVAL_TO_EXIT_METRIC_NAME))