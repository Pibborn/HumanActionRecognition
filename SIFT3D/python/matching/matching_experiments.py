from SIFT3D.python.settings import Constants
from SIFT3D.python.videodescription import vocab_creation, descriptor_evaluation
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)
from sklearn import svm, neighbors
from sklearn.model_selection import train_test_split
from sklearn import preprocessing



def weissman_experiment_multiple(times):
    total_yeahs = 0
    total_noes = 0
    for i in range(0, times):
        yeah, noes = weissman_experiment()
        total_yeahs += yeah
        total_noes += noes
    logging.info("After "+str(times)+" Weissman experiments:")
    logging.info(""+ str(total_yeahs) + " correct predictions")
    logging.info(""+ str(total_noes) + " wrong predictions")
    logging.info(""+ str(total_yeahs/times) + " accuracy")

def vocab_experiment(size, c=0.001):
    #dicts, y = vocabCreation.generate_vocabulary(Constants.DATA_DIR + '/descriptors/weissman-yash/', size)

    dicts, y = vocab_creation.load_vocab_from_size(Constants.DATA_DIR + 'vocabs/bbrister-2grams-window/',
                                                   Constants.WEISSMAN_DATASET_DIR, size)

    #train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 10)
    #X_train, y_train = load_descriptors(train_videos)

    X_train, X_test, y_train, y_test = train_test_split(dicts, y, test_size=0.1, stratify=y)

    scaler = preprocessing.StandardScaler().fit(X_train)
    scaler.transform(X_train)
    scaler.transform(X_test)

    #X_test, X_dev, y_test, y_dev = train_test_split(X_test, y_test, test_size=0.5, stratify=y_test)


    #best_params_dict = estimate_hyperparameters(X_dev, y_dev)

    #k = estimate_hyperparameters(X_train, y_train)

    model = svm.LinearSVC(C=1e-3)
    #model = svm.SVC(**best_params_dict)
    #model = neighbors.KNeighborsClassifier(n_neighbors=15)
    model.fit(X_train, y_train)
    logging.info("Done fitting.")

    #yeah, noes = majority_voting(model, test_videos)
    #logging.info("Done voting.")

    #model = xgb_model(dicts, y)
    accuracy = model.score(X_train, y_train)
    logging.info("Achieved " + str(accuracy) + " accuracy on the training set")
    #logging.info("By majority rule, " + str(yeah) + " successes and " + str(noes) + " failures")
    #logging.info("Good for " + str(yeah / (yeah + noes)) + " accuracy")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def vocab_experiment_multiple_sizes(size_arr):
    accuracies = []
    for size in size_arr:
        logging.info('Trying size '+ str(size) + ':')
        accuracy = vocab_experiment(size)
        accuracies.append(accuracy)
    mean = sum(accuracies) / len(accuracies)
    logging.info('Achieved ' + str(mean) + ' accuracies over ' + str(len(accuracies)) + ' tries.')

def vocab_experiment_multiple(times, size=250, c=0.001):
    accuracies = []
    for i in range(0, times):
        accuracy = vocab_experiment(size, c=c)
        accuracies.append(accuracy)
    mean = sum(accuracies)/len(accuracies)
    logging.info('Achieved '+str(mean)+' accuracies over '+str(times)+' tries.')

def random_experiment(size):
    random_dataset_dir = Constants.DATA_DIR + '/weizmann/random/'
    dicts, y = vocab_creation.generate_vocabulary_with_pruning(random_dataset_dir, size, model=None)
    X_train, X_test, y_train, y_test = train_test_split(dicts, y, test_size=0.1, random_state=42)

    model = svm.LinearSVC(C=0.001)
    # model = neighbors.KNeighborsClassifier(15).fit(X_train, y_train)
    model.fit(X_train, y_train)

    # model = xgb_model(dicts, y)
    accuracy = model.score(X_train, y_train)
    logging.info("Achieved " + str(accuracy) + " accuracy on the training set")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def random_experiment_multiple_sizes(size_arr):
    for size in size_arr:
        random_experiment(size)


def majority_voting_weighted(X_test, y_test, y_pred, X_test_tfidf):
    scores = [0 for i in range(0, Constants.WEISSMAN_LABEL_NUM)]
    for i in range(0, len(X_test)):
        xi = X_test[i]
        yi = y_pred[i]

        scores[yi] += 1 * X_test_tfidf[i]

    high_score = max(scores)
    final_pred = scores.index(high_score)

    print('Final prediction: ' + str(final_pred))
    print('Actual label: ' + str(y_test[0]))
    print(scores)

    if final_pred == y_test[0]:
        return 1
    else:
        return 0



if __name__ == "__main__":
    sizes = [100, 250, 500, 750, 1000, 1250, 1500]
    modes = ['threshold']

    #bigram_cluster_sizes = [7, 10, 16, 23, 27, 32, 36, 39, 45, 50]

    #trigram_cluster_sizes = [4, 5, 7, 8, 9, 10, 11, 12, 20]

    #for size in sizes:
    #    vocab_experiment_multiple(20, size=size)
    for size in sizes:
        #dicts, y = vocabCreation.generate_ngram_vocab(Constants.DATA_DIR + '/descriptors/bbrister-kth/',
        #                                             Constants.DATA_DIR + '/features/bbrister-kth/', size, n=2, ngram_strategy='window')
        dicts, y = vocab_creation.generate_vocabulary(Constants.DATA_DIR + '/descriptors/bbrister-kth/', size=size)
    #    print(dicts)

    # # tfidf experiments
    # times = 20
    # successes = 0
    # for mode in modes:
    #     for i in range(0, times):
    #         # split and load descriptors
    #         train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 1)
    #         X_train, y_train = load_descriptors(train_videos)
    #         X_test, y_test = load_descriptors(test_videos)
    #
    #         # train the evaluation model
    #         vocab_size = 500
    #         #tfidf_evaluator = descriptorEvaluation.TFIDF_Evaluator(vocab_size, Constants.WEISSMAN_LABEL_NUM)
    #         #tfidf_evaluator.train(X_train, y_train)
    #         cluster_evaluator = descriptorEvaluation.contestedClusterEvaluator(vocab_size, Constants.WEISSMAN_LABEL_NUM)
    #         cluster_evaluator.train(X_train, y_train)
    #
    #         # train the k-neighbors model
    #         model = neighbors.KNeighborsClassifier(15)
    #         model.fit(X_train, y_train)
    #         y_pred = model.predict(X_test)
    #
    #         # get the weights for the test data and vote by majority
    #         #X_test_tfidf = tfidf_evaluator.get_evaluation(X_test, y_pred)
    #         X_test_cluster_goodness = cluster_evaluator.get_evaluation(X_test, mode=mode)
    #         #X_test_tfidf = [1 for xi in X_test]
    #         success = majority_voting_weighted(X_test, y_test, y_pred, X_test_cluster_goodness)
    #         logging.info('Experiment state was ' + str(success))
    #         successes += success
    #
    # logging.info('Average over ' + str(times) + ' tries : ' + str(successes / times))

    #weissman_experiment_multiple(2)
    #vocab_experiment_multiple_sizes(sizes)
    #for size in sizes:
    #    vocab_experiment_multiple(20, size=size)
    #vocab_experiment_multiple_sizes(sizes)
    #random_experiment_multiple_sizes(sizes)


    # experiments in directly recognizing descriptor classes
    '''
    train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 10)
    X, y = load_descriptors(train_videos)
    mean_X = np.mean(X)
    X -= mean_X
    #y = np_utils.to_categorical(y, 10)
    #model = neural_net_model(X, y)
    model = svm.SVC()
    model.fit(X, y)
    #model.fit(X, y, verbose=1, nb_epoch=80)

    logging.info('Obtained '+ str(model.score(X, y)) + ' accuracy on the training set')
    X_test, y_test = load_descriptors(test_videos)
    X_test -= mean_X
    #y_test = np_utils.to_categorical(y_test, 10)
    score = model.score(X_test, y_test)
    #score = model.evaluate(X_test, y_test)
    print(score)
    model.save('mymodel-6.keras')
    #yeah, noes = majority_voting(model, test_videos)
    #logging.info('Obtained '+ str(yeah/yeah+noes) + ' accuracy on the test set')
    '''


    #weissman_experiment_multiple(5)