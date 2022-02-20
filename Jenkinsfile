pipeline {
  agent none
  stages {
    stage('build') {
      parallel {
        stage('Arm 32 bit') {
          environment {
            ARCH = 'arm'
            CROSS_COMPILE = 'arm-bytebox-linux-gnueabihf-'
          }
          agent {
            docker {
              image 'mengdemao/bytebox-compiler:latest'
              // args '-v ${env.WORKSPACE}:/playground:rw'
            }
          }
          steps {
            sh 'git submodule update --init --recursive --force'
            sh './build.sh all'
          }
          post {
            cleanup {
              sh 'git clean -ff -x -d .'
            }
          }
        }

        stage('Arm 64 bit') {
          environment {
            ARCH = 'arm64'
            CROSS_COMPILE = 'aarch64-bytebox-linux-gnu-'
          }
          agent {
            docker {
              image 'mengdemao/bytebox-compiler:latest'
              // args '-v ${env.WORKSPACE}:/playground:rw'
            }
          }
          steps {
            echo "NAME = ${env.WORKSPACE}"
            sh 'git submodule update --init --recursive --force'
            sh './build.sh all'
          }
          post {
            cleanup {
              sh 'git clean -ff -x -d .'
            }
          }
        }
      } // parallel
    } // stage('build')
  } // stages

  options {
    buildDiscarder(logRotator(numToKeepStr: '10', artifactDaysToKeepStr: '30'))
    timeout(time: 60, unit: 'MINUTES')
  }
}
