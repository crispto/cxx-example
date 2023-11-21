export_to_onnx: 将 yolov8 模型转换为 onnx 格式
onnx_demo  使用 onnx 进行 yolov8 的模型推理
yolo-demo 直接使用 YOLO 模型跑图片检测推理和可视化
utils 里包含可视化代码
video_demo 使用 onnx 进行视频流的检测推理和可视化
yolo-demo 直接使用 YOLO 模型跑图片检测推理和可视化

bench
| Tensorrt | CUDA  | CPU
| --- | --- |
| 0.053 | 0.002 | 0.003
```
  ncalls  tottime  percall  cumtime  percall filename:lineno(function)
     3599  191.341    0.053  191.378    0.053 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:202(run)
     3599   68.933    0.019   68.933    0.019 {method 'write' of 'cv2.VideoWriter' objects}
        2    0.000    0.000   44.343   22.172 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:358(__init__)
        2   44.343   22.172   44.343   22.172 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:434(_create_inference_session)
     3599   28.002    0.008   28.002    0.008 {resize}
     3601   11.062    0.003   11.062    0.003 {method 'read' of 'cv2.VideoCapture' objects}
     3599    1.002    0.000    7.621    0.002 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:84(nms)
   209675    4.462    0.000    5.173    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:25(getInter)
     4245    3.182    0.001    3.182    0.001 {method 'astype' of 'numpy.ndarray' objects}
     3599    0.371    0.000    1.682    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/scripts/detect/utils.py:13(draw_onnx)


## GPU
      ncalls  tottime  percall  cumtime  percall filename:lineno(function)
      601    9.313    0.015    9.313    0.015 {method 'write' of 'cv2.VideoWriter' objects}
      601    8.371    0.014    8.378    0.014 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:202(run)
        1    0.000    0.000    3.829    3.829 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:358(__init__)
        1    3.829    3.829    3.829    3.829 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:434(_create_inference_session)
      601    0.185    0.000    1.723    0.003 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:84(nms)
      601    1.615    0.003    1.615    0.003 {resize}
    30477    1.103    0.000    1.249    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:25(getInter)
      603    1.128    0.002    1.128    0.002 {method 'read' of 'cv2.VideoCapture' objects}
      648    0.596    0.001    0.596    0.001 {method 'astype' of 'numpy.ndarray' objects}
      601    0.080    0.000    0.293    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/scripts/detect/utils.py:13(draw_onnx)


   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
      601   28.528    0.047   28.535    0.047 /home/SENSETIME/yangchengwei/miniconda3/envs/dl/lib/python3.10/site-packages/onnxruntime/capi/onnxruntime_inference_collection.py:202(run)
      601    9.340    0.016    9.340    0.016 {method 'write' of 'cv2.VideoWriter' objects}
      601    0.191    0.000    1.764    0.003 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:84(nms)
      601    1.672    0.003    1.672    0.003 {resize}
    30477    1.132    0.000    1.280    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/./scripts/detect/onnx_bench.py:25(getInter)
      603    1.106    0.002    1.106    0.002 {method 'read' of 'cv2.VideoCapture' objects}
      648    0.592    0.001    0.592    0.001 {method 'astype' of 'numpy.ndarray' objects}
        1    0.479    0.479    0.479    0.479 {namedWindow}
      601    0.081    0.000    0.296    0.000 /home/SENSETIME/yangchengwei/900G/coding/github/laboratory/libtest/libtorch/scripts/detect/utils.py:13(draw_onnx)
     2865    0.149    0.000    0.149    0.000 {putText}

```
