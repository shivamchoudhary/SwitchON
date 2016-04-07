import logging


def SwitchONlogger(name):
    formatter = logging.Formatter(fmt='level=[%(levelname)s] - module = ['
            '%(module)s] - Function = [%(funcName)s] - linenum=[%(lineno)d]'
            '- msg = [%(message)s]')
    handler = logging.StreamHandler()
    handler.setFormatter(formatter)

    logger = logging.getLogger(name)
    logger.setLevel(logging.DEBUG)
    logger.addHandler(handler)
    return logger
