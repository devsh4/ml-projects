# -*- coding: utf-8 -*-
"""
Created on Sat Oct  7 19:23:41 2017

@author: Dev Shah
"""
#DIGIT RECOGNIZER


import argparse
import sys
from tensorflow.examples.tutorials.mnist import input_data
import tensorflow as tf

FLAGS = None

def main(_):
  # Import data
  mnist = input_data.read_data_sets(FLAGS.data_dir, one_hot=True)
  
  # Create the model
  x = tf.placeholder(tf.float32, [None, 784])
  W = tf.Variable(tf.zeros([784, 10]))
  b = tf.Variable(tf.zeros([10]))
  y = tf.matmul(x, W) + b

  # Define loss and optimizer
  y_ = tf.placeholder(tf.float32, [None, 10])
  
  # Using tf.nn.softmax_cross_entropy_with_logits on the raw
  # outputs of 'y', and then averaging across the batch.
  cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=y))
  #Use gradient descent to minimize entropy
  train = tf.train.GradientDescentOptimizer(0.6).minimize(cross_entropy)

  #starting tensorflow session
  session = tf.InteractiveSession()
  #initializing tf variables
  tf.global_variables_initializer().run()
  
  #Train
  for _ in range(1000): 
    batch_xs, batch_ys = mnist.train.next_batch(100)
    session.run(train, feed_dict={x: batch_xs, y_: batch_ys})

  #Test trained model
      #gives booleans whether or not it is a correct prediction
  correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
      #takes mean of all predictions
  accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
      #prints accuracy rate when model is run on test set
  print('Accuracy rate: ',session.run(accuracy*100, feed_dict={x: mnist.test.images,
                                      y_: mnist.test.labels}))
  
  
if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  
  #specifying default directory in args 
  parser.add_argument('--data_dir', type=str, default= 'C:/Users/Dev Shah/Downloads/Projects/digit recognizer/input_data',
                      help='Directory for storing input data')
  
  FLAGS, unparsed = parser.parse_known_args()
  
  #run
  tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)