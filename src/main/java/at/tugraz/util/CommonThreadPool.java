package at.tugraz.util;


import java.util.Collection;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;


public class CommonThreadPool implements ExecutorService
{
	private static final int size = InfrastructureAnalyzer.getLocalParallelism();
	private static final ExecutorService shared = ForkJoinPool.commonPool();
	private final ExecutorService _pool;
	public static ExecutorService triggerRemoteOPsPool = null;

	public CommonThreadPool(ExecutorService pool) {
		_pool = pool;
	}

	public static ExecutorService get(int k) {
		return new CommonThreadPool( (size==k) ?
			shared : Executors.newFixedThreadPool(k));
	}
	
	public static <T> void invokeAndShutdown(ExecutorService pool, Collection<? extends Callable<T>> tasks) {
		try {
			//execute tasks
			List<Future<T>> ret = pool.invokeAll(tasks);
			//check for errors and exceptions
			for( Future<T> r : ret )
				r.get();
			//shutdown pool
			pool.shutdown();
		}
		catch(Exception ex) {
			throw new RuntimeException(ex);
		}
	}

	public static void shutdownShared() {
		shared.shutdownNow();
	}

	public static void shutdownAsyncRDDPool() {
		if (triggerRemoteOPsPool != null) {
			//shutdown prefetch/broadcast thread pool
			triggerRemoteOPsPool.shutdown();
			triggerRemoteOPsPool = null;
		}
	}

	@Override
	public void shutdown() {
		if( _pool != shared )
			_pool.shutdown();
	}

	@Override
	public List<Runnable> shutdownNow() {
		return ( _pool != shared ) ?
			_pool.shutdownNow() : null;
	}

	@Override
	public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks) throws InterruptedException {
		return _pool.invokeAll(tasks);
	}

	@Override
	public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit)
			throws InterruptedException {
		return _pool.invokeAll(tasks, timeout, unit);
	}
	
	@Override
	public void execute(Runnable command) {
		_pool.execute(command);
	}

	@Override
	public <T> Future<T> submit(Callable<T> task) {
		return _pool.submit(task);
	}

	@Override
	public <T> Future<T> submit(Runnable task, T result) {
		return _pool.submit(task, result);
	}

	@Override
	public Future<?> submit(Runnable task) {
		return _pool.submit(task);
	}

	
	//unnecessary methods required for API compliance
	@Override
	public boolean isShutdown() {
		throw new RuntimeException();
	}

	@Override
	public boolean isTerminated() {
		throw new RuntimeException();
	}

	@Override
	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
		throw new RuntimeException();
	}

	@Override
	public <T> T invokeAny(Collection<? extends Callable<T>> tasks) throws InterruptedException, ExecutionException {
		throw new RuntimeException();
	}

	@Override
	public <T> T invokeAny(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit)
			throws InterruptedException, ExecutionException, TimeoutException {
		throw new RuntimeException();
	}
}
