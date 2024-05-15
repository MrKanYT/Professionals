import cv2


def read_qr_code(bgr_image: cv2.UMat) -> str | None:

    qcd = cv2.QRCodeDetector()
    retval, decoded_info, points, straight_qrcode = qcd.detectAndDecodeMulti(bgr_image)
    for c in decoded_info:
        if c:
            return c


def test():
    pass

if __name__ == "__main__":
    test()



