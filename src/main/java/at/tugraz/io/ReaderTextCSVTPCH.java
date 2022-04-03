package at.tugraz.io;

import at.tugraz.objects.tpch.Customer;
import at.tugraz.objects.tpch.LineItem;
import at.tugraz.objects.tpch.Nation;
import at.tugraz.objects.tpch.Order;
import at.tugraz.objects.tpch.Part;
import at.tugraz.objects.tpch.Region;
import at.tugraz.objects.tpch.Supplier;
import at.tugraz.util.RootObject;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ReaderTextCSVTPCH extends ReaderText {

	private String regionPath;
	private String nationPath;
	private String partPath;
	private String supplierPath;
	private String customerPath;
	private String lineItemPath;
	private String orderPath;

	private HashMap<Integer, Region> regionMap = new HashMap<Integer, Region>();
	private HashMap<Integer, Nation> nationMap = new HashMap<Integer, Nation>();
	private HashMap<Integer, Part> partMap = new HashMap<Integer, Part>();
	private HashMap<Integer, Supplier> supplierMap = new HashMap<Integer, Supplier>();
	private HashMap<Integer, ArrayList<LineItem>> lineItemMap = new HashMap<Integer, ArrayList<LineItem>>();
	private HashMap<Integer, ArrayList<Order>> orderMap = new HashMap<>();

	@Override public ArrayList<RootObject> getObjects(String fileName) {
		this.nationPath = fileName + "/nation.tbl";
		this.regionPath = fileName + "/region.tbl";
		this.partPath = fileName + "/part.tbl";
		this.supplierPath = fileName + "/supplier.tbl";
		this.customerPath = fileName + "/customer.tbl";
		this.lineItemPath = fileName + "/lineitem.tbl";
		this.orderPath = fileName + "/orders.tbl";

		loadRegionData();
		loadNationData();
		loadPartData();
		loadSupplierData();
		loadLineItemData();
		loadOrderData();

		try(BufferedReader br = new BufferedReader(new FileReader(customerPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);

				int customerKey = Integer.parseInt(data[0]);
				Nation nation = nationMap.get(Integer.parseInt(data[3]));
				ArrayList<Order> orders = orderMap.get(customerKey);
				Customer customer = new Customer(orders, nation, customerKey, data[1], data[2], data[4], Double.parseDouble(data[5]), data[6], data[7]);
				objects.add(customer);

			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}

		return objects;
	}

	// Load Region Data
	private void loadRegionData() {
		try(BufferedReader br = new BufferedReader(new FileReader(regionPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Region region = new Region(Integer.parseInt(data[0]), data[1], data[2]);
				regionMap.put(region.getRegionKey(), region);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Nation Data
	private void loadNationData() {
		try(BufferedReader br = new BufferedReader(new FileReader(nationPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Region region = regionMap.get(Integer.parseInt(data[2]));
				Nation nation = new Nation(Integer.parseInt(data[0]), data[1], region, data[3]);
				nationMap.put(nation.getNationKey(), nation);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Part Data
	private void loadPartData() {
		try(BufferedReader br = new BufferedReader(new FileReader(partPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Part part = new Part(Integer.parseInt(data[0]), data[1], data[2], data[3], data[4], Integer.parseInt(data[5]), data[6], Double.parseDouble(data[7]), data[8]);
				partMap.put(part.getPartKey(), part);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Supplier Data
	private void loadSupplierData() {
		try(BufferedReader br = new BufferedReader(new FileReader(supplierPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Nation nation = nationMap.get(Integer.parseInt(data[3]));
				Supplier supplier = new Supplier(Integer.parseInt(data[0]), data[1], data[2], nation, data[4], Double.parseDouble(data[5]), data[6]);
				supplierMap.put(supplier.getSupplierKey(), supplier);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Order Data
	private void loadOrderData() {
		try(BufferedReader br = new BufferedReader(new FileReader(orderPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);

				int orderKey = Integer.parseInt(data[0]);
				int customerKey = Integer.parseInt(data[1]);

				List<LineItem> lineItems = lineItemMap.get(orderKey);
				Order order = new Order(orderKey, lineItems, customerKey, data[2], Double.parseDouble(data[3]), data[4], data[5], data[6], Integer.parseInt(data[7]), data[8]);

				ArrayList<Order> orderTmp;
				if(orderMap.containsKey(customerKey))
					orderTmp = orderMap.get(customerKey);
				else
					orderTmp = new ArrayList<>();
				orderTmp.add(order);
				orderMap.put(customerKey, orderTmp);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load LineItem Data
	private void loadLineItemData() {
		try(BufferedReader br = new BufferedReader(new FileReader(lineItemPath))) {
			String line;
			while((line = br.readLine()) != null) {
				String[] data = getData(line);

				int orderKey = Integer.parseInt(data[0]);
				int partKey = Integer.parseInt(data[1]);
				int supplierKey = Integer.parseInt(data[2]);

				// get the Part
				Part partTmp;
				if(partMap.containsKey(partKey))
					partTmp = partMap.get(partKey);
				else
					throw new RuntimeException("There is no such Part");

				// get the Supplier
				Supplier supplierTmp;
				if(supplierMap.containsKey(supplierKey))
					supplierTmp = supplierMap.get(supplierKey);
				else
					throw new RuntimeException("There is no such Supplier");

				LineItem lineItem = new LineItem(orderKey, supplierTmp, partTmp, Integer.parseInt(data[3]), Double.parseDouble(data[4]), Double.parseDouble(data[5]), Double.parseDouble(data[6]),
					Double.parseDouble(data[7]), data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);

				ArrayList<LineItem> lineItemTemp;
				if(lineItemMap.containsKey(orderKey))
					lineItemTemp = lineItemMap.get(orderKey);
				else
					lineItemTemp = new ArrayList<>();

				lineItemTemp.add(lineItem);
				lineItemMap.put(orderKey, lineItemTemp);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	private String[] getData(String line) {
		String[] data = line.split("\\|");
		return data;
	}
}
