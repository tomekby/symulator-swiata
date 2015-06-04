import abc

class General(object):
    __metaclass__ = abc.ABCMeta

    # Serializacja obiektu do warstwy nośnika
    @abc.abstractclassmethod
    def serialize(self, obj):
        """
        :param object: obiekt do serializacji
        :return: format odpowiedni do zapisu
        """

    # Deserializacja z warstwy nośnika do obiektu
    @abc.abstractclassmethod
    def deserialize(self, obj):
        """
        :param object: obiekt/dane do deserializacji
        :return: zdeserializowany obiekt
        """
