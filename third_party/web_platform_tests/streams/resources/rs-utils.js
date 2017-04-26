'use strict';
(function () {

  class RandomPushSource {
    constructor(toPush) {
      this.pushed = 0;
      this.toPush = toPush;
      this.started = false;
      this.paused = false;
      this.closed = false;

      this._intervalHandle = null;
    }

    readStart() {
      if (this.closed) {
        return;
      }

      if (!this.started) {
        this._intervalHandle = setInterval(writeChunk, 2);
        this.started = true;
      }

      if (this.paused) {
        this._intervalHandle = setInterval(writeChunk, 2);
        this.paused = false;
      }

      const source = this;
      function writeChunk() {
        if (source.paused) {
          return;
        }

        source.pushed++;

        if (source.toPush > 0 && source.pushed > source.toPush) {
          if (source._intervalHandle) {
            clearInterval(source._intervalHandle);
            source._intervalHandle = undefined;
          }
          source.closed = true;
          source.onend();
        } else {
          source.ondata(randomChunk(128));
        }
      }
    }

    readStop() {
      if (this.paused) {
        return;
      }

      if (this.started) {
        this.paused = true;
        clearInterval(this._intervalHandle);
        this._intervalHandle = undefined;
      } else {
        throw new Error('Can\'t pause reading an unstarted source.');
      }
    }
  }

  function randomChunk(size) {
    let chunk = '';

    for (let i = 0; i < size; ++i) {
      // Add a random character from the basic printable ASCII set.
      chunk += String.fromCharCode(Math.round(Math.random() * 84) + 32);
    }

    return chunk;
  }

  function readableStreamToArray(readable, reader) {
    if (reader === undefined) {
      reader = readable.getReader();
    }

    const chunks = [];

    return pump();

    function pump() {
      return reader.read().then(result => {
        if (result.done) {
          return chunks;
        }

        chunks.push(result.value);
        return pump();
      });
    }
  }

  class SequentialPullSource {
    constructor(limit, options) {
      const async = options && options.async;

      this.current = 0;
      this.limit = limit;
      this.opened = false;
      this.closed = false;

      this._exec = f => f();
      if (async) {
        this._exec = f => setTimeout(f, 0);
      }
    }

    open(cb) {
      this._exec(() => {
        this.opened = true;
        cb();
      });
    }

    read(cb) {
      this._exec(() => {
        if (++this.current <= this.limit) {
          cb(null, false, this.current);
        } else {
          cb(null, true, null);
        }
      });
    }

    close(cb) {
      this._exec(() => {
        this.closed = true;
        cb();
      });
    }
  }

  function sequentialReadableStream(limit, options) {
    const sequentialSource = new SequentialPullSource(limit, options);

    const stream = new ReadableStream({
      start() {
        return new Promise((resolve, reject) => {
          sequentialSource.open(err => {
            if (err) {
              reject(err);
            }
            resolve();
          });
        });
      },

      pull(c) {
        return new Promise((resolve, reject) => {
          sequentialSource.read((err, done, chunk) => {
            if (err) {
              reject(err);
            } else if (done) {
              sequentialSource.close(err2 => {
                if (err2) {
                  reject(err2);
                }
                c.close();
                resolve();
              });
            } else {
              c.enqueue(chunk);
              resolve();
            }
          });
        });
      }
    });

    stream.source = sequentialSource;

    return stream;
  }


  self.RandomPushSource = RandomPushSource;
  self.readableStreamToArray = readableStreamToArray;
  self.sequentialReadableStream = sequentialReadableStream;

}());
