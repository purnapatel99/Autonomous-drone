import cv2
import numpy as np
import os

def resize(path, target, scale):
    for name in os.listdir(path):
        file_path = path + '/' + name
        print(file_path)
        img = cv2.imread(file_path)
        print(np.shape(img))

        width = int(img.shape[1] * scale)
        height = int(img.shape[0] * scale)
        dim = (width, height)

        # resize image
        img = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)
        print("done")
        cv2.imshow("img", img)
        cv2.waitKey(1000)
        os.chdir(target)
        cv2.imwrite(name, img)

def create_neg(img_path, file_path):
    for name in os.listdir(img_path):
        if name[-3:] != 'jpg':
            continue
        img_full = img_path + '/' + name
        print(img_full)
        file = open(file_path, "a")
        file.write(img_full + '\n')
        file.close()


def trainer(cv_directory: object, data_directory: object, num: object) -> object:
    annotation = cv_directory + r'\opencv\build\x64\vc15\bin\opencv_annotation ' + '--annotations=' + data_directory + '\pos.txt --images=' + data_directory
    create_samples = cv_directory + r'\opencv\build\x64\vc15\bin\opencv_createsamples.exe -info ' + data_directory + '\pos.txt -w 24 -h 24 -num ' + str(num) + ' -vec ' + data_directory + '/pos.vec'
    train = cv_directory + r'\opencv\build\x64\vc15\bin\opencv_traincascade.exe -data ' + data_directory + r'\train -vec ' + data_directory + '\pos.vec -bg ' + data_directory + r'\neg.txt -numPos ' + str(num) + ' -numNeg ' + str(num) + ' -numStages 10' \
                                                                                                                                                                                                                                               ' -w 24 -h 24' + '-maxs'

    # annotation = 'sudo ' + cv_directory + r'/opencv/build/x64/vc15/bin/opencv_annotation.exe ' + '--annotations=' + data_directory + 'pos.txt --images=' + data_directory
    # create_samples = 'sudo ' + cv_directory + r'/opencv/build/x64/vc15/bin/opencv_createsamples.exe -info' + data_directory + 'pos.txt -w 24 -h 24 -num' + str(
    #     num) + '-vec ' + data_directory + '/pos.vec'
    # train = 'sudo ' + cv_directory + r'/opencv/build/x64/vc15/bin/opencv_traincascade.exe -data' + data_directory + r'/train -vec ' + data_directory + '/pos.vec -bg ' + data_directory + r'/neg.txt -numPos ' + str(
    #     num) + ' -numNeg ' + str(num) + ' -numStages 10 -w 24 -h 24'

    print(annotation)
    print(create_samples)
    print(train)

    # os.system(annotation)
    print('done')
    # os.system(create_samples)
    print('done')
    os.system(train)
    print('done')

if __name__ == '__main__':

    # create_neg(r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve', r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\neg.txt')

    # path = '/home/prasham/Downloads/chess_target/negative_knight'
    # target = '/home/prasham/Downloads/chess_target'
    # #
    # resize(path, target, 0.1)
    # print (cv2.__version__)
    # # terminal run:  opencv_annotation --annotations=/home/prasham/Downloads/chess_knight_data/pos.txt --images=/home/prasham/Downloads/chess_knight_data
    #
    # #os.system(r"C:\Users\purna\Downloads\opencv\build\x64\vc15\bin\opencv_annotation --annotations=C:\Users\purna\Downloads\chess_target/pos.txt --images=C:\Users\purna\Downloads\chess_target\chess_target")
    # os.system(r'C:\Users\purna\Downloads\opencv\build\x64\vc15\bin\opencv_createsamples.exe -info C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\pos.txt -w 24 -h 24 -num 7 -vec C:\Users\purna\Downloads\chess_target\chess_target\knigth_positve/pos.vec')
    # os.system(r'C:\Users\purna\Downloads\opencv\build\x64\vc15\bin\opencv_traincascade.exe -data C:\Users\purna\Downloads\chess_target\train -vec C:\Users\purna\Downloads\chess_target/pos.vec -bg C:\Users\purna\Downloads\chess_target\neg.txt -numPos 5 -numNeg 100 -numStages 10 -w 24 -h 24')
    trainer(r'C:\Users\purna\Downloads', r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve', 100)

    classifier = cv2.CascadeClassifier(r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\train\cascade.xml')
    img = cv2.imread(r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\20211201_162406.jpg')
    rectangles = classifier.detectMultiScale(img, 1.04, 6)
    print(rectangles)

    for rec in rectangles:
        frame = cv2.rectangle(img, (rec[0], rec[1]), (rec[2], rec[3]), (255, 0, 0))
        cv2.imshow('img', frame)
        cv2.waitKey(1000)
    # cap = cv2.VideoCapture(0)
    # i = 1
    # while i < 10:
    #     frame, _ = cap.read()
    #     cv2.imshow("img", frame)
    #     cv2.waitKey(10)
    #     print(i)
    #     i = i +1
    #
    # while 1:
    #     frame, _ = cap.read()
    #     cv2.imshow("img", frame)
    #     cv2.waitKey(10000)
    #     rectangles = classifier.detectMultiScale(frame)
    #     print(rectangles)

    # trainer(r'C:\Users\purna\Downloads', r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve', 100)
    # name = 'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\pos.txt'
    # i = 12
    # while (i < 100):
    #     # name = r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\\' + str(i) + '.jpg'
    #     # cv2.imwrite(name, img)
    #     # print(i)
    #
    #     file = open(r'C:\Users\purna\Downloads\chess_target\chess_target\knight_positve\pos.txt', "a")
    #     file.write(str(i) + '.jpg 1 137 170 87 154' + '\n')
    #     file.close()
    #     i = i+1


