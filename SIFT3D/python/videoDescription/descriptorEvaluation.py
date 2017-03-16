import glob

import numpy as np
from scipy.spatial.distance import cosine
from sklearn import preprocessing
from sklearn.cluster import KMeans
import SIFT3D.python.utils as utils
from SIFT3D.python import matching_experiments as match
from SIFT3D.python.utils import Constants, infer_label
import logging
import csv

class TFIDF_Evaluator:

    def __init__(self, size, num_classes):
        self.clustering_model = None
        self.size = size
        self.num_classes = num_classes
        self.term_frequency_matrix = np.zeros((num_classes, size), dtype=np.int)
        self.word_class_occurrence_matrix = np.zeros((num_classes, size), dtype=np.int)

    def train(self, X, y, c = None):
        if self.clustering_model == None:
            self.clustering_model = KMeans(n_clusters=self.size, tol=1e-2)

        if c == None:
            clusters = self.clustering_model.fit_predict(X, y)
        else:
            clusters = c

        for i in range(0, len(y)):
            yi = y[i]
            ci = clusters[i]

            self.term_frequency_matrix[yi][ci] += 1

        #print(term_frequency_matrix)

        for j in range(0, self.num_classes):
            for i in range(0, len(clusters)):
                yi = y[i]
                ci = clusters[i]
                if yi != j:
                    continue
                else:
                    if self.word_class_occurrence_matrix[yi][ci] < self.num_classes:
                        self.word_class_occurrence_matrix[yi][ci] += 1
                    else:
                        continue

        print(self.word_class_occurrence_matrix)

    def get_evaluation(self, X, y):
        clusters = self.clustering_model.predict(X)
        X_tfidf = []
        for i in range(0, len(X)):
            xi = X[i]
            yi = y[i]
            ci = clusters[i]

            xi_tf = 0.5 + 0.5 * (self.term_frequency_matrix[yi][ci] / max(self.term_frequency_matrix[:, ci]))

            xi_idf = np.log10((self.num_classes + 1) / (1 + self.word_class_occurrence_matrix[yi][ci]))

            X_tfidf.append(xi_tf * xi_idf)

        return X_tfidf


class contestedClusterEvaluator:

    def __init__(self, size, num_classes):
        self.clustering_model = None
        self.size = size
        self.num_classes = num_classes
        self.term_frequency_matrix = np.zeros((num_classes, size), dtype=np.float)

    def train(self, X, y, c = None):
        if self.clustering_model == None:
            self.clustering_model = KMeans(n_clusters=self.size, tol=1e-2)

        if c == None:
            clusters = self.clustering_model.fit_predict(X, y)
        else:
            clusters = c
        logging.info('Done clustering')

        for i in range(0, len(y)):
            yi = y[i]
            ci = clusters[i]

            self.term_frequency_matrix[yi][ci] += 1

        #print(self.term_frequency_matrix)

        for a_cluster in range(0, self.size):
            all_term_occurrences = sum(self.term_frequency_matrix[:, a_cluster])
            for a_class in range(0, self.num_classes):
                self.term_frequency_matrix[a_class][a_cluster] = \
                    self.term_frequency_matrix[a_class][a_cluster] / float(all_term_occurrences)

        #print(self.term_frequency_matrix)

    def get_evaluation(self, X, mode='cosine', threshold=0.5):
        # input validation
        if mode not in ['cosine', 'log-cosine', 'threshold']:
            print('Invalid evaluation mode.')
            return

        X_goodness = []

        clusters = self.clustering_model.predict(X)

        bad_array = [1/self.num_classes for i in range(0, self.num_classes)]

        for i in range(0, len(X)):
            xi = X[i]
            ci = clusters[i]

            cluster_goodness_array = self.term_frequency_matrix[:, ci].T

            xi_goodness = None

            if mode == 'cosine':
                xi_goodness = 1 / cosine(bad_array, cluster_goodness_array)
            if mode == 'log-cosine':
                xi_goodness = np.log(1 / cosine(bad_array, cluster_goodness_array))
            if mode == 'threshold':
                if cosine(bad_array, cluster_goodness_array) > threshold:
                    xi_goodness = 0
                else:
                    xi_goodness = 1

            assert xi_goodness != None

            X_goodness.append(xi_goodness)

        return X_goodness




