<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">


	<!-- nastaveni jazyka (defaultne cestina)-->
	<xsl:variable name="lng">cz</xsl:variable>




  <msxsl:script language="JScript" implements-prefix="dedek">

	function RGB(val, max)
	{
		return "#ff"
			 	+ hex2(val/max)
				+ hex2(val/max);
	}

	function hex2(cislo)
	{
		var ret = (255 - Math.round(cislo * 255)).toString(16);

		if (ret.length == 1)
			return "0" + ret;
		else
			return ret;
	}



	function hex(cislo)
	{
		return cislo.toString(16);
	}

  </msxsl:script>


<!-- klic - atributy-->
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />

<!-- klic - hypotezy (Kody: kvuli pocitani sum sloupcu - mozna zkusit najit lepsi reseni)-->
<xsl:key name="key_hyp_sdkl" match="hyp_sdkl" use="@id" />


<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="SumShow">false</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="ColourHighlighting">false</xsl:variable>
<xsl:variable name="TypeOfValues">Absolute</xsl:variable>
<xsl:variable name="BorderGrey">true</xsl:variable>



<!-- nastaveni jazykovych popisku (labelu) -->


<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


<xsl:variable name="label_set_number">   <!-- nadpis tabulky: cislo mnoziny-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>Second set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


    
<!-- TEMPLATES -->



      

	<xsl:template match="hyp_sdkl">

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderGrey='true'">#eeeeee</xsl:when>
				<xsl:otherwise>#ffffff</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="pocet_radku">
				<xsl:if test="$SumShow='true'"><xsl:value-of select="count(tab[position()=1]/r) + 2" /></xsl:if>
				<xsl:if test="$SumShow='false'"><xsl:value-of select="count(tab[position()=1]/r) + 1" /></xsl:if>
		</xsl:variable>
		
		<xsl:variable name="pocet_sloupcu">
				<xsl:if test="$SumShow='true'"><xsl:value-of select="count(tab[position()=1]/r[position()=1]/c) + 2" /></xsl:if>
				<xsl:if test="$SumShow='false'"><xsl:value-of select="count(tab[position()=1]/r[position()=1]/c) + 1" /></xsl:if>
		</xsl:variable>

		
		<xsl:variable name="sum_of_values" select="@sum2" />
		
		<xsl:variable name="total">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@sum2" />
				</xsl:when>
				<xsl:when test="$TypeOfValues='Relative'">100</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="row_attr_id">
			<xsl:value-of select="@row_attributes" />
		</xsl:variable>
		
		<xsl:variable name="col_attr_id">
			<xsl:value-of select="@column_attributes" />
		</xsl:variable>
		
		<xsl:variable name="row_attr_name">
			<xsl:value-of select="key('key_ti_attribute',$row_attr_id)/@quant" />
		</xsl:variable>
		
		<xsl:variable name="col_attr_name">
			<xsl:value-of select="key('key_ti_attribute',$col_attr_id)/@quant" />
		</xsl:variable>

		
		<xsl:variable name="hyp_id" select="@id" />

		<paragraph>
		
			
			<!-- Create element "table"-->
			
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				
				
				<!-- first row of table-->
				<tr id="{$id_base}r0">
							<td id="{$id_base}r0d0" bgcolor="{$border_color}">
								<xsl:value-of select="$row_attr_name"/> \ <xsl:value-of select="$col_attr_name"/>
								<xsl:if test="$TypeOfValues='Relative'">
									<text id="{$id_base}r0d0text"> (%)</text> 
								</xsl:if>
							</td>
							
							<xsl:for-each select="key('key_ti_attribute',$col_attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r0d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="$border_color" />
									</xsl:attribute>
									
									<text id="{$id_base}r0d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>	
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true'">
								<td id="{$id_base}r0d_sum" bgcolor="{$border_color}">
									<text id="{$id_base}r0d_sum_text"><xsl:value-of select="$label_sum"/></text>
								</td>
							</xsl:if>
				</tr>
				
				
				<!-- further rows of table -->
				
				<xsl:for-each select="tab[position()=2]/r">
					<xsl:variable name="row_number" select="position()" />
					<xsl:variable name="row_values_sum" select="sum(c/@val)" />  <!-- sum of values in this row -->
					
					<tr id="{$id_base}r{$row_number}">
					
						<td id="{$id_base}r{$row_number}d0" bgcolor="{$border_color}">
							<text id="{$id_base}r{$row_number}d0text">
									<xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" />
							</text> 
						</td>
						
						<xsl:for-each select="c">
							<xsl:variable name="col_number" select="position()" />
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r<xsl:value-of select="$row_number" />d<xsl:value-of select="$col_number" />
								</xsl:attribute>
								
								<xsl:if test="$ColourHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values))" />
									</xsl:attribute>
								</xsl:if>
								
								<text id="{$id_base}r{$row_number}d{$col_number}text">
									<xsl:if test="$TypeOfValues='Absolute'">
										<xsl:value-of select="@val" />
									</xsl:if>
								
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:value-of select="round((@val div $sum_of_values)*100)" />
									</xsl:if>
									
								</text> 
							</xsl:element>	
							
						</xsl:for-each>
						
						<xsl:if test="$SumShow='true'">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base"/>r<xsl:value-of select="$row_number"/><xsl:text>d_sum</xsl:text>
									</xsl:attribute>
									
									<xsl:if test="$ColourHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number($row_values_sum), number($sum_of_values))" />
										</xsl:attribute>
									</xsl:if>
									
									<text id="{$id_base}r{$row_number}d_sum_text">
										<xsl:if test="$TypeOfValues='Absolute'">
											<xsl:value-of select="$row_values_sum" />
										</xsl:if>
								
										<xsl:if test="$TypeOfValues='Relative'">
											<xsl:value-of select="round(($row_values_sum div $sum_of_values)*100)" />
										</xsl:if>
									</text>
								</xsl:element>
						</xsl:if>
						
					</tr>
					
				</xsl:for-each>
				
				
				<!-- last row of table (sum of values) -->
				<!-- Kody - trochu prasecina, ale lip asi nejde. Pomoci klice hypotezy. -->
				
				<xsl:if test="$SumShow='true'">
					<tr id="{$id_base}r_sum">
					
						<td id="{$id_base}r_sum_d0" bgcolor="{$border_color}">
							<text id="{$id_base}r_sum_d0text"><xsl:value-of select="$label_sum"/></text>
						</td>
				
						<xsl:for-each select="tab[position()=2]/r[position()=1]/c">
							<xsl:variable name="col_number" select="position()" />	
							<xsl:variable name="sum_of_column" select="sum(key('key_hyp_sdkl',$hyp_id)/tab[position()=2]/r/c[position()=$col_number]/@val)" />
						
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r_sum_d<xsl:value-of select="$col_number" />
								</xsl:attribute>
								
								<xsl:if test="$ColourHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number($sum_of_column), number($sum_of_values))" />
									</xsl:attribute>
								</xsl:if>
								
								<text id="{$id_base}r_sum_d{$col_number}text">
										<xsl:if test="$TypeOfValues='Absolute'">
											<xsl:value-of select="$sum_of_column" />
										</xsl:if>
								
										<xsl:if test="$TypeOfValues='Relative'">
											<xsl:value-of select="round(($sum_of_column div $sum_of_values)*100)" />
										</xsl:if>
								</text>
							</xsl:element>
					
						</xsl:for-each>
						
						<td id="{$id_base}r_sum_d_total_sum">
								<text id="{$id_base}r_sum_d_total_sum_text">
									<xsl:if test="$TypeOfValues='Absolute'">
										<xsl:value-of select="$sum_of_values" />
									</xsl:if>
								
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:value-of select="round(($sum_of_values div $sum_of_values)*100)" />
									</xsl:if>
								</text>
						</td>
					
					</tr>
					
				</xsl:if>
				
				
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:text>Tab: </xsl:text><xsl:value-of select="$label_set_number"/><br/></text> 
			</xsl:if>
				
				
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
