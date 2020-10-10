function search (number, sortedArray){
	var end=sortedArray.length-1;
	var start=0;

	if (number>sortedArray[end]){
		console.log (`The number ${number} is not found !`);
		return false;
	}
	if (number<sortedArray[start]){
		console.log (`The number ${number} is not found !`);
		return false;
	}
	while (start<=end)
	{
		var mid= Math.floor((end+start)/2);
		// console.log (`The mid  is ${mid}`);	
		if (sortedArray[mid] == number)
		{
			console.log (`The number ${number} found !`);
			return true;
		}
		else if (sortedArray[mid]<number)
		{
				
			start=mid+1;
			// console.log (`The start is ${start}`);		
		}
		else	
		{
				
			end=mid-1;
			// console.log (`The end is ${end}`);
		}
		
	}
	console.log (`The number ${number} not found !`);
	return false;

}

var arr=[1,3,4,7];
// search (3,arr);

// search (4,arr);
// search (5,arr);
// search (5,arr);

for(var num=0; num<10;num++)
{
	search (num,arr);
};